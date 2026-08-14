#pragma once
#include <cstddef>
#include <cstdint>
#include "storage_device.h"
#include "sample_source.h"

class PCMSampleSource : public StorageSampleSource {
public:
    PCMSampleSource(StorageDevice& storage)
     : storage(storage_) {}

    bool init() override;
    bool start(std::size_t clipStartSector) override;
    void reset() override;
    bool getSamples(int16_t* destination, std::size_t sampleCount) override;
    std::size_t getReadPositionSamples() const override;

private:
    static constexpr MAX_BLOCK_SIZE_BYTES = 1024;

    bool readStorage(std::size_t block, uint8_t* buffer);

    int16_t workspace_[MAX_BLOCK_SIZE_BYTES / sizeof(int16_t)];
    StorageDevice& storage_;
    std::size_t workspaceIndex_ = 0;
    std::size_t workspaceSectorOffset_ = 0;
};
