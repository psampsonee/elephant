#pragma once
#include "audio_sink.h"
#include <cstdint>

class AudioSinkFake : public AudioSink {
public:
    explicit AudioSinkFake(bool fail_all_public_functions = false)
        : fail_all_public_functions_(fail_all_public_functions)
    {
    }

    bool prepare(uint16_t sampleRateHz) override;
    bool start() override;
    bool writeSample(int16_t sample) override;
    bool stop() override;
    bool silence() override;

    void consumeSample();

    int16_t lastSampleWritten() const { return lastSample_; }
    uint32_t samplesWritten() const { return samplesWritten_; }
    bool isSilenced() const { return isSilenced_; }
    bool isStopped() const { return isStopped_; }
    bool isPrepareCalled() const { return isPrepareCalled_; }

private:
    int16_t lastSample_ = 0;
    uint32_t samplesWritten_ = 0;
    uint16_t preparedSampleRateHz_ = 0;
    bool isSilenced_ = false;
    bool isStopped_ = false;
    bool isStarted_ = false;
    bool isPrepareCalled_ = false;

    bool fail_all_public_functions_ = false;
};
