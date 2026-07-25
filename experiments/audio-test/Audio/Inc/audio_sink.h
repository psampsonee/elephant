#pragma once
#include <stdint.h>

class AudioSink {
public:
    virtual ~AudioSink() = default;

    virtual bool writeSample(int16_t sample) = 0;
    virtual bool stop() = 0;
    virtual bool silence() = 0;
    virtual bool prepare(uint32_t sampleRateHz) = 0;
    virtual bool start() = 0;
    virtual bool isSampleNeeded() const = 0;
};
