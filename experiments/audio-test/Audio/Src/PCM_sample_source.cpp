#pragma once
#include <cstddef>
#include <cstdint>
#include "storage_device.h"
#include "sample_source.h"

/* Initialization
 * Prepares SampleSource upon system startup
 * Tasks:
 * Check that startup invariants are valid.
 * Initialize storage
 * Call reset()
 */
bool PCMSampleSource::init() {
    reset();

    if (storage_.getBlockSize() > MAX_BLOCK_SIZE_BYTES) {
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
bool start(size_t clipStartSector) {
    workspaceIndex_ = 0;
    workspaceSectorOffset_ = clipStartSector;

    if(!readStorage(
        workspaceSectorOffset_,
        reinterpret_cast<uint8_t*>(sampleWorkspace
        ))) {
        return false; // If very first read fails, something may have gone wrong with initialization; throw an error.
    }

    ready_ = true;
    return true;
}

/* Reset
 * Tasks:
 * Set all parameters to initial states.
 */
void PCMSampleSource::reset() {
    workspaceSectorOffset_ = 0;
}

/* getSample
 * Tasks:
 * Check runtime invariants and prevent them from being violated:
 * Can't get a sample when the source is not ready.
 * Sample workspace size >= storage device block size
 *
 * destination aways gets written to starting at index 0.
 */

    // workspaceIndex_ is a persistent variable starting at 0.
    // upon start(clipStartSector), workspace_ is filled with the first block.
    // samplesPerBlock = storage_.getBlockSize() / sizeof(int16_t)
    // samplesRemaining = sampleCount
    // samplesWritten = 0
    // While samplesRemaining > 0:
    //  samplesLeftInWorkspace = samplesPerBlock - workspaceIndex_
    //  if ( samplesLeftInWorkspace == 0 ):
    //      workspaceSectorOffset_ += 1
    //      workspaceIndex_ = 0
    //      write the contents of the block into the workspace as int16_t
    //      continue
    //  samplesToCopy = min(samplesRemaining, samplesLeftInWorkspace)
    //  For every i from 0 to samplesToCopy-1:
    //   destination[i+samplesWritten] = workspace_[workspaceIndex_]
    //   workspaceIndex_ += 1
    //  samplesWritten += samplesToCopy
    //  samplesRemaining -= samplesToCopy

bool PCMSampleSource::getSamples(int16_t* destination, std::size_t sampleCount) {

    if(!ready_) {
        return true;
    }

    std::size_t samplesPerBlock = storage_.getBlockSize() / sizeof(int16_t);
    std::size_t samplesRemaining = sampleCount;
    std::size_t samplesWritten = 0;

    while ( samplesRemaining > 0 ) {
        std::size_t samplesLeftInWorkspace = samplesPerBlock - workspaceIndex_;

        if (samplesLeftInWorkspace == 0) {
            workspaceIndex_ = 0;
            workspaceSectorOffset_ += 1;
            if(!readStorage(
                workspaceSectorOffset_,
                reinterpret_cast<uint8_t*>(workspace_)
                )) {
                return false;
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

    return true;
}

std::size_t PCMSampleSource::getReadPositionSamples() const {
    if(!ready_) {
        return 0;
    }

    return sampleReadPosition_;
}

bool PCMSampleSource::readStorage(std::size_t block, uint8_t*buffer) {
        auto readResult=storage_.read(block, buffer);

        if (readResult == StorageDevice::ReadResult::Error) {
            return false;
        }

        if (readResult == StorageDevice::ReadResult::NotReady) {
            return true; // no fatal error, but leave buffer needing refill
        }
}
