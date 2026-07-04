#pragma once
#include "storage_device.h"
#include <cstdint>
#include <cstddef>

class StorageDeviceFake : public StorageDevice {
public:
    explicit StorageDeviceFake(bool failInit = false, bool failRead = false)
        : failInit_(failInit), failRead_(failRead) {}

    bool init() override;
    bool read(uint32_t block, uint8_t* buffer) override;

    uint32_t getReadCount() const { return readCount_; }
    bool getIsInitialized() const { return isInitialized_; }
    static uint16_t getBufSize() { return BUF_SIZE; }

private:
    static constexpr uint16_t BUF_SIZE = 512;
    uint32_t readCount_ = 0;

    bool failInit_ = false;
    bool failRead_ = false;
    bool isInitialized_ = false;
};
