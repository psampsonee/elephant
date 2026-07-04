#include "storage_device_fake.h"

bool StorageDeviceFake::init() {
    if(failInit_) return false;

    isInitialized_ = true;
    return true;
}

bool StorageDeviceFake::read(uint32_t block, uint8_t* buffer) {
    (void)block;

    if (failRead_) return false;
    if (!isInitialized_) return false;
    if (buffer == nullptr) return false;

    for(int i = 0; i < BUF_SIZE; i++) {
        buffer[i] = static_cast<uint8_t>(i);
    }

    readCount_++;
    return true;
}

