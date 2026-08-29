#include "storage_device.h"
#include "sample_source.h"
#include "ADPCM_sample_source.h"

/* Initialization
 * Prepares SampleSource upon system startup
 * Tasks:
 * Check that startup invariants are valid:
 * Sample workspace size >= storage device sector size
 * Initialize storage
 * Call reset()
 */
bool ADPCMSampleSource::init() {
    reset();

    if (storage_.getSectorSize() > MAX_SECTOR_SIZE_BYTES) {
        return false;
    }

    if (!storage_.init()) {
        return false;
    }

    return true;
}

/* Start
 * Tasks:
 * Set all sample parameters to first reading state
 */
bool ADPCMSampleSource::start(size_t clipStartSector) {
    compressedBufferSectorOffset_ = clipStartSector;

    ReadResult compressedBufferFillResult = fillCompressedBuffer();

    if(compressedBufferFillResult != ReadResult::Success) {
        return false; // Starting on a NotReady is not good.
    }

    if(!fillWorkspace()) {
        return false;
    }

    ready_ = true;
    return true;
}

/* Reset
 * Tasks:
 * Set all parameters to initial states.
 */
void ADPCMSampleSource::reset() {
    std::memset(workspace_, 0, sizeof(workspace_));

    workspaceIndex_ = 0;
    workspaceSampleCount_ = 0;
    clipSamplesToDestination_ = 0;

    std::memset(compressedBuffer_, 0, sizeof(compressedBuffer_));
    compressedBufferIndex_ = 0;
    compressedBufferSectorOffset_ = 0;

    samplesLeftInFrame_ = 0;
    frameHeaderIndex_ = 0;

    currentByte_ = 0;
    highNibble_ = false;
    sampleState_ = {};
}

bool ADPCMSampleSource::getSamples(int16_t* destination, std::size_t sampleCount) {

    if(!ready_) {
        return false;
    }

    std::size_t samplesRemaining = sampleCount;
    std::size_t samplesWritten = 0;

    while ( samplesRemaining > 0 ) {
        std::size_t samplesLeftInWorkspace = workspaceSampleCount_ - workspaceIndex_;

        if (samplesLeftInWorkspace == 0) {
            if(!fillWorkspace()) {
                return false;
            }

            if(workspaceSampleCount_ == 0) {
                return true;
            }

            continue;
        }

        std::size_t samplesToCopy =
            ( samplesLeftInWorkspace > samplesRemaining ?
            samplesRemaining : samplesLeftInWorkspace );

        for (std::size_t i = 0; i < samplesToCopy; i++) {
            destination[samplesWritten+i] = workspace_[workspaceIndex_];
            workspaceIndex_ += 1;
        }

        samplesWritten += samplesToCopy;
        samplesRemaining -= samplesToCopy;
    }

    clipSamplesToDestination_ += samplesWritten;
    return true;
}

std::size_t ADPCMSampleSource::getReadPositionSamples() const {
    if(!ready_) {
        return 0;
    }

    return clipSamplesToDestination_;
}

ReadResult ADPCMSampleSource::fillCompressedBuffer() {
    auto nextSector = compressedBufferSectorOffset_ + 1;
    auto readResult=storage_.read(
        compressedBufferSectorOffset_,
        reinterpret_cast<uint8_t*>(compressedBuffer_));

    if (readResult == ReadResult::Error) {
        return ReadResult::Error;
    }

    if (readResult == ReadResult::NotReady) {
        return ReadResult::NotReady; // no fatal error, but leave buffer needing refill
    }

    compressedBufferIndex_ = 0;
    compressedBufferSectorOffset_ = nextSector;
    return ReadResult::Success;
}

bool ADPCMSampleSource::fillWorkspace() {
    workspaceSampleCount_ = 0;
    workspaceIndex_ = 0;

    while (workspaceSampleCount_ < WORKSPACE_CAPACITY) {

        if (samplesLeftInFrame_ == 0) {
            ReadResult frameStartResult = startADPCMFrame();

            if(frameStartResult == ReadResult::NotReady) {
                return true;
            }

            if(frameStartResult == ReadResult::Error) {
                return false;
            }

            continue;
        }

        ReadResult decodedSampleResult = getNextDecodedSample();

        if(decodedSampleResult == ReadResult::NotReady) {
            return true;
        }

        if(decodedSampleResult == ReadResult::Error) {
            return false;
        }
    }

    return true;
}

ReadResult ADPCMSampleSource::startADPCMFrame() {
    using namespace ima_adpcm;
    auto* frameHeaderBytes = reinterpret_cast<uint8_t*>(&frameHeader_);

    while(frameHeaderIndex_ < 4) {
        auto byteReadResult = getNextCompressedByte();

        if (byteReadResult != ReadResult::Success) {
            return byteReadResult;
        }

        frameHeaderBytes[frameHeaderIndex_] = currentByte_;
        frameHeaderIndex_ += 1;
    }

    frameHeaderIndex_ = 0;

    workspace_[workspaceSampleCount_] = frameHeader_.iSample;
    workspaceSampleCount_ += 1;
    sampleState_.predictor = frameHeader_.iSample;
    sampleState_.stepIndex = frameHeader_.iIndex;
    highNibble_ = false;

    samplesLeftInFrame_ = FRAME_SAMPLE_COUNT - 1;
    return ReadResult::Success;
}

ReadResult ADPCMSampleSource::getNextDecodedSample() {
    if(samplesLeftInFrame_ == 0) {
        return ReadResult::NotReady;
    }

    if(!highNibble_) {
        auto byteReadResult = getNextCompressedByte();

        if (byteReadResult != ReadResult::Success) {
            return byteReadResult;
        }
    }

    uint8_t code = ima_adpcm::code(currentByte_, highNibble_);
    int16_t currentSample = ima_adpcm::sample(code, sampleState_);

    workspace_[workspaceSampleCount_] = currentSample;
    workspaceSampleCount_++;

    highNibble_ = !highNibble_;
    samplesLeftInFrame_ -= 1;
    return ReadResult::Success;
}

ReadResult ADPCMSampleSource::getNextCompressedByte()
{
    if(compressedBufferIndex_ >= storage_.getSectorSize()) {

        ReadResult compressedBufferFillResult = fillCompressedBuffer();

        if(compressedBufferFillResult != ReadResult::Success) {
            return compressedBufferFillResult;
        }
    }

    currentByte_ = compressedBuffer_[compressedBufferIndex_];
    compressedBufferIndex_ += 1;
    return ReadResult::Success;
}
