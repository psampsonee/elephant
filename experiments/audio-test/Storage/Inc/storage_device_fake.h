#pragma once
#include "storage_device.h"
#include <string.h>
#include <cstdint>
#include <cstddef>
#include <algorithm>

class StorageDeviceFake : public StorageDevice {
public:
    static constexpr size_t SECTORS_MAX = 400;
    static constexpr size_t SECTOR_SIZE = 512;

    struct StorageData {
        uint8_t data[SECTORS_MAX][SECTOR_SIZE]{};
        size_t sectorCount = 0;
        size_t sampleCount = 0;
    };

    explicit StorageDeviceFake(bool failInit = false, bool failRead = false, size_t sectorCount = 0, size_t sampleCount = 0, bool preloadData = false)
        : failInit_(failInit), failRead_(failRead), preloadData_(preloadData) {
            data_.sectorCount = std::min(sectorCount, SECTORS_MAX);
            data_.sampleCount = sampleCount;
        }

    bool init() override;
    ReadResult read(std::size_t sector, uint8_t* buffer) override;

    StorageData& getStorageData() { return data_; }
    const StorageData& getStorageData() const { return data_; }

    uint32_t getReadCount() const { return readCount_; }
    bool getIsInitialized() const { return isInitialized_; }

    void setReady(bool ready) { isReady_ = ready; }
    void setFailRead(bool failRead) { failRead_ = failRead; }

    std::size_t getSectorSize() { return 512; }

private:
    uint32_t readCount_ = 0;

    void setStorageData();

    StorageData data_ {};

    bool failInit_ = false;
    bool failRead_ = false;
    bool isInitialized_ = false;
    bool isReady_ = false;
    bool preloadData_ = false;
};
