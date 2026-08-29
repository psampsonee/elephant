#pragma once
#include <cstddef>
#include <cstdint>
#include <cstring>
#include "storage_device.h"
#include "ADPCM_codec.h"
#include "storage_sample_source.h"

class ADPCMSampleSource : public StorageSampleSource {
public:
    ADPCMSampleSource(StorageDevice& storage)
    : StorageSampleSource(storage) {}

    bool init() override;
    bool start(std::size_t clipStartSector) override;
    void reset() override;
    bool getSamples(int16_t* destination, std::size_t sampleCount) override;
    std::size_t getReadPositionSamples() const override;

private:
    static constexpr std::size_t WORKSPACE_CAPACITY = 512;
    static constexpr std::size_t MAX_SECTOR_SIZE_BYTES = 1024;

    bool fillWorkspace();

    ReadResult fillCompressedBuffer();
    ReadResult startADPCMFrame();
    ReadResult getNextDecodedSample();
    ReadResult getNextCompressedByte();

    int16_t workspace_[WORKSPACE_CAPACITY] {};

    std::size_t workspaceIndex_ = 0;
    std::size_t workspaceSampleCount_ = 0;
    std::size_t clipSamplesToDestination_ = 0;

    uint8_t compressedBuffer_[MAX_SECTOR_SIZE_BYTES] {};
    std::size_t compressedBufferIndex_ = 0;
    std::size_t compressedBufferSectorOffset_ = 0;

    std::size_t samplesLeftInFrame_ = 0;
    std::size_t frameHeaderIndex_ = 0;

    ima_adpcm::IMA_ADPCM_FRAMEHEADER frameHeader_ = {};
    static_assert(sizeof(frameHeader_) == 4);

    uint8_t currentByte_ = 0;
    bool highNibble_ = false;
    ima_adpcm::SampleState sampleState_ = {};

#ifdef UNIT_TEST
    // Unit test variable accessors:
public:
    int16_t debug_getWorkspaceSample(std::size_t index)
    { return index < WORKSPACE_CAPACITY ? workspace_[index] : 0; }

    std::size_t debug_getWorkspaceIndex() { return workspaceIndex_; }
    std::size_t debug_getWorkspaceSampleCount() { return workspaceSampleCount_; }
    std::size_t debug_getClipSamplesToDestination() { return clipSamplesToDestination_; }

    uint8_t debug_getCompressedBufferByte(std::size_t index)
    { return index < MAX_SECTOR_SIZE_BYTES ? compressedBuffer_[index] : 0; }
    std::size_t debug_getCompressedBufferIndex() { return compressedBufferIndex_; }
    std::size_t debug_getCompressedBufferSectorOffset() { return compressedBufferSectorOffset_; }

    std::size_t debug_getSamplesLeftInFrame() { return samplesLeftInFrame_; }
    std::size_t debug_getSrameHeaderIndex() { return frameHeaderIndex_; }
#endif

};
