#include "storage_device_fake.h"
#include <cassert>
#include <cstdint>
#include <cstring>
#include <iostream>

static constexpr size_t BLOCK_COUNT = 10;
static constexpr size_t SAMPLE_COUNT = 1000;

struct StorageDeviceFakeTestConfig {
    bool storageFailInit = false;
    bool storageFailRead = false;
    size_t blockCount = BLOCK_COUNT;
    size_t sampleCount = SAMPLE_COUNT;
};

struct StorageDeviceFakeTestHandles {
    StorageDeviceFake storage;

    StorageDeviceFakeTestHandles(StorageDeviceFakeTestConfig cfg = { })
        : storage(cfg.storageFailInit, cfg.storageFailRead, cfg.blockCount, cfg.sampleCount) {}

    StorageDeviceFakeTestHandles(const StorageDeviceFakeTestHandles&) = delete;
    StorageDeviceFakeTestHandles& operator=(const StorageDeviceFakeTestHandles&) = delete;
};
