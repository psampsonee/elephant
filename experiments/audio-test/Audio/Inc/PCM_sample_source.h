#pragma once
#include <cstddef>
#include <cstdint>
#include "storage_device.h"
#include "sample_source.h"

class PCMSampleSource : public StorageSampleSource {
public:
    PCMSampleSource(StorageDevice& storage)
     : storage(storage_) {}

    bool init() override;
    bool start(std::size_t clipStartSector) override;
    bool reset() override;
    bool getSamples(int16_t* destination, std::size_t sampleCount) override;
    std::size_t getReadPositionSamples() const override;

private:
    StorageDevice& storage_;

    size_t sampleReadPosition_;
};
