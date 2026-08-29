#pragma once
#include "storage_device_fake.h"
#include "ADPCM_sample_source.h"
#include <cassert>
#include <cstdint>
#include <cstring>
#include <iostream>

static constexpr size_t SECTOR_COUNT = 10;
static constexpr size_t SAMPLE_COUNT = 1000;
static constexpr size_t INITIAL_SECTOR = 0;
static constexpr size_t SECTOR_SIZE_BYTES = 512;
static constexpr size_t BUF_SIZE_SAMPLES = SECTOR_COUNT*SECTOR_SIZE_BYTES;

struct ADPCMSampleSourceTestConfig {
    bool storageFailInit = false;
    bool storageFailRead = false;
    size_t sectorCount = SECTOR_COUNT;
    size_t sampleCount = SAMPLE_COUNT;
};

struct ADPCMSampleSourceTestHandles {
    StorageDeviceFake storage;
    ADPCMSampleSource source;

    ADPCMSampleSourceTestHandles(ADPCMSampleSourceTestConfig cfg = {})
        : storage(
            cfg.storageFailInit,
            cfg.storageFailRead,
            cfg.sectorCount,
            cfg.sampleCount
        ),
        source(storage) {}

    void setStorageData(const uint8_t* data, size_t size);

    ADPCMSampleSourceTestHandles(const ADPCMSampleSourceTestHandles&) = delete;
    ADPCMSampleSourceTestHandles& operator=(const ADPCMSampleSourceTestHandles&) = delete;
};
