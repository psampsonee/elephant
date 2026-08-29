#include "storage_device_fake.h"

void StorageDeviceFake::setStorageData() {
    for (size_t sector = 0; sector < data_.sectorCount; ++sector) {
        for (size_t byte = 0; byte < SECTOR_SIZE; ++byte)
        {
            data_.data[sector][byte] =
            static_cast<uint8_t>((sector * 17 + byte) & 0xFF);
        }
    }
}

bool StorageDeviceFake::init() {
    if(failInit_) return false;

    if(!preloadData_) setStorageData();

    isInitialized_ = true;
    isReady_ = true;
    return true;
}

ReadResult StorageDeviceFake::read(std::size_t sector, uint8_t* buffer) {

    if (failRead_ ||
        !isInitialized_ ||
        buffer == nullptr ||
        sector >= data_.sectorCount)
    {
        return ReadResult::Error;
    }

    if (!isReady_)
    {
        return ReadResult::NotReady;
    }

    memcpy(buffer, data_.data[sector], SECTOR_SIZE);

    readCount_++;
    return ReadResult::Success;
}
