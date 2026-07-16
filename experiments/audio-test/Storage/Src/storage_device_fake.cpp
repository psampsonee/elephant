#include "storage_device_fake.h"

void StorageDeviceFake::setStorageData() {
    for (size_t block = 0; block < data_.blockCount; ++block) {
        for (size_t byte = 0; byte < BLOCK_SIZE; ++byte)
        {
            data_.data[block][byte] =
            static_cast<uint8_t>((block * 17 + byte) & 0xFF);
        }
    }
}

bool StorageDeviceFake::init() {
    if(failInit_) return false;

    setStorageData();

    isInitialized_ = true;
    isReady_ = true;
    return true;
}

StorageDevice::ReadResult StorageDeviceFake::read(uint32_t block, uint8_t* buffer) {

    if (failRead_ ||
        !isInitialized_ ||
        buffer == nullptr ||
        block >= data_.blockCount)
    {
        return ReadResult::Error;
    }

    if (!isReady_)
    {
        return ReadResult::NotReady;
    }

    memcpy(buffer, data_.data[block], BLOCK_SIZE);

    readCount_++;
    return ReadResult::Success;
}
