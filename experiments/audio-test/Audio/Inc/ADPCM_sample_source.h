#pragma once
#include <cstddef>
#include <cstdint>
#include "storage_device.h"

class ADPCMSampleSource : public StorageSampleSource {
public:
    ADPCMSampleSource(StorageDevice& storage);

    bool init() override;
    bool reset() override;
    bool getSamples(int16_t* destination, std::size_t sampleCount) override;
    std::size_t getReadPositionSamples() const override;

private:

    bool getNextSample(int16_t& sample);
    bool beginNextBlock();

    std::size_t compressedOffset_;
    std::size_t readPositionSamples_;
    std::size_t blockBytesRemaining_;

    uint8_t currentByte_;
    bool highNibble_;

    SampleState state_;
    StorageDevice& storage_;
};
