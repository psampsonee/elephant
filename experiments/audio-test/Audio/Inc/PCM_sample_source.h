#pragma once
#include <cstddef>
#include <cstdint>
#include <cstring>
#include "storage_device.h"
#include "storage_sample_source.h"

class PCMSampleSource : public StorageSampleSource {
public:
    PCMSampleSource(StorageDevice& storage)
     : StorageSampleSource(storage) {}

    bool init() override;
    bool start(std::size_t clipStartSector) override;
    void reset() override;
    bool getSamples(int16_t* destination, std::size_t sampleCount) override;
    std::size_t getReadPositionSamples() const override;

    int16_t getWorkspaceSample_debug(std::size_t index)
    { return index < MAX_BLOCK_SIZE_BYTES / sizeof(int16_t) ?
        workspace_[index] : 0; }

#ifdef UNIT_TEST
    std::size_t debug_getWorkspaceIndex() { return workspaceIndex_; }
    std::size_t debug_getWorkspaceSectorOffset() { return workspaceSectorOffset_; }
#endif

private:
    static constexpr std::size_t MAX_BLOCK_SIZE_BYTES = 1024;

    bool fillWorkspace();

    int16_t workspace_[MAX_BLOCK_SIZE_BYTES / sizeof(int16_t)] {};

    bool workspaceValid_ = false;
    std::size_t workspaceIndex_ = 0;
    std::size_t workspaceSectorOffset_ = 0;
};
