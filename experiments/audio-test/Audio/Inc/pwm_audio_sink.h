#pragma once
#include "audio_sink.h"
#include "main.h"

class PwmAudioSink : public AudioSink{
public:
    PwmAudioSink(TIM_HandleTypeDef& carrierTimer, TIM_HandleTypeDef& sampleUpdateTimer)
        : carrierTimer_(carrierTimer), sampleUpdateTimer_(sampleUpdateTimer) {}

    bool writeSample(int16_t sample) override;
    bool stop() override;
    bool silence() override;
    bool prepare(uint32_t sampleRateHz) override;
    bool start() override;
    bool isSampleNeeded() const override { return isSampleNeeded_; }

    bool isSilenced() const { return isSilenced_; }
    bool isStopped() const { return isStopped_; }
    bool isPrepareCalled() const { return isPrepareCalled_; }

    void handleSampleInterrupt();

#ifdef UNIT_TEST
    void debug_updatePeak(int16_t sample);
#endif

private:
    static constexpr int16_t PULSE_CENTER   = 62;
    static constexpr int16_t PULSE_VARIANCE = 40;
    static constexpr uint32_t MAX_SAMPLERATE_HZ = 100000;
    static constexpr uint16_t SAMPLE_RATE_HZ = 48000;
    static constexpr uint16_t PCM_PEAK = 32768;

    volatile bool isSampleNeeded_ = false;
    volatile uint16_t nextPulseValue_ = PULSE_CENTER;
    uint32_t sampleRateHz_ = 0;

    bool isSilenced_ = true;
    bool isStopped_ = true;
    bool isPrepareCalled_ = false;

    uint16_t pulseValue (int16_t sample) const;
    uint16_t counterPeriod (uint32_t sampleRateHz) const;

    int16_t debug_peakPlayed_ = 0;

    TIM_HandleTypeDef& carrierTimer_;
    TIM_HandleTypeDef& sampleUpdateTimer_;
};
