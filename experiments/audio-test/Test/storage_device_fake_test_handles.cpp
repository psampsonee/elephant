#include "storage_device_fake.h"
#include <cassert>
#include <cstdint>
#include <cstring>
#include <iostream>

struct StorageDeviceFakeTestConfig {
    bool storageFailInit = false;
    bool storageFailRead = false;
    size_t blockCount = 10;
    size_t sampleCount = 1000;
};

struct StorageDeviceFakeTestHandles {
    StorageDeviceFake storage;

    StorageDeviceFakeTestHandles(StorageDeviceFakeTestConfig cfg = { })
        : storage(cfg.storageFailInit, cfg.storageFailRead, cfg.blockCount, cfg.sampleCount) {}

    StorageDeviceFakeTestHandles(const StorageDeviceFakeTestHandles&) = delete;
    StorageDeviceFakeTestHandles& operator=(const StorageDeviceFakeTestHandles&) = delete;
};
