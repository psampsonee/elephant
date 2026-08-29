#pragma once
#include "storage_device_fake.h"
#include "PCM_sample_source.h"
#include <cassert>
#include <cstdint>
#include <cstring>
#include <iostream>

static constexpr size_t BLOCK_COUNT = 10;
static constexpr size_t SAMPLE_COUNT = 1000;

struct PCMSampleSourceTestConfig {
    bool storageFailInit = false;
    bool storageFailRead = false;
    size_t blockCount = BLOCK_COUNT;
    size_t sampleCount = SAMPLE_COUNT;
};

struct PCMSampleSourceTestHandles {
    StorageDeviceFake storage;
    PCMSampleSource source;

    PCMSampleSourceTestHandles(PCMSampleSourceTestConfig cfg = {})
        : storage(
            cfg.storageFailInit,
            cfg.storageFailRead,
            cfg.blockCount,
            cfg.sampleCount
        ),
        source(storage) {}

    PCMSampleSourceTestHandles(const PCMSampleSourceTestHandles&) = delete;
    PCMSampleSourceTestHandles& operator=(const PCMSampleSourceTestHandles&) = delete;
};
