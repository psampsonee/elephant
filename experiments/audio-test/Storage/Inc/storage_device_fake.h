#pragma once
#include "storage_device.h"
#include <string.h>
#include <cstdint>
#include <cstddef>
#include <algorithm>

class StorageDeviceFake : public StorageDevice {
public:
    static constexpr size_t BLOCKS_MAX = 400;
    static constexpr size_t BLOCK_SIZE = 512;

    struct StorageData {
        uint8_t data[BLOCKS_MAX][BLOCK_SIZE]{};
        size_t blockCount = 0;
        size_t sampleCount = 0;
    };

    explicit StorageDeviceFake(bool failInit = false, bool failRead = false, size_t blockCount = 0, size_t sampleCount = 0)
        : failInit_(failInit), failRead_(failRead) {
            data_.blockCount = std::min(blockCount, BLOCKS_MAX);
            data_.sampleCount = sampleCount;
        }

    bool init() override;
    ReadResult read(std::size_t block, uint8_t* buffer) override;

    StorageData& getStorageData() { return data_; }
    const StorageData& getStorageData() const { return data_; }

    uint32_t getReadCount() const { return readCount_; }
    bool getIsInitialized() const { return isInitialized_; }

    void setReady(bool ready) { isReady_ = ready; }

    std::size_t getBlockSize() { return 512; }

private:
    uint32_t readCount_ = 0;

    void setStorageData();

    StorageData data_ {};

    bool failInit_ = false;
    bool failRead_ = false;
    bool isInitialized_ = false;
    bool isReady_ = false;
};
