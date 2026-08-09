#pragma once
#include <cstddef>
#include <cstdint>
#include "storage_device.h"
#include "sample_source.h"

bool PCMSampleSource::init() {
    // Initialize storage device
    if (!storage_.init()) {
        enterError();
        return;
    }

    return storage.init();
}

bool start(size_t clipStartSector) {
    nextSectorToRead_ = clipStartSector;

}

bool PCMSampleSource::reset() {
    nextSectorToRead_ = 0;
    sampleReadPosition_ = 0;
}

bool PCMSampleSource::getSamples(int16_t* destination, std::size_t sampleCount) {

    auto readResult=storage_.read(nextSectorToRead_, dst);

    if (readResult == StorageDevice::ReadResult::Error) {
        return false;
    }

    if (readResult == StorageDevice::ReadResult::NotReady) {
        return true; // no fatal error, but leave buffer needing refill
    // }

    nextSectorToRead_++;
}

std::size_t PCMSampleSource::getReadPositionSamples() const {
    return sampleReadPosition_;
}
