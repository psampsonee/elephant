#pragma once
#include <cstdint>

class AudioSink {
public:
    virtual bool writeSample(int16_t sample) = 0;
    virtual bool stop() = 0;
    virtual bool silence() = 0;
    virtual bool prepare(uint16_t sampleRateHz) = 0;
    virtual bool start() = 0;
    virtual bool isSampleNeeded() const { return isSampleNeeded_; }

protected:
    bool isSampleNeeded_ = true;
};
