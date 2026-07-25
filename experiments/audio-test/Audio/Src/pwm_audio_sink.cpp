#include "pwm_audio_sink.h"
#include <iostream>

void PwmAudioSink::debug_updatePeak(int16_t sample) {
    int16_t& peak = debug_peakPlayed_;
    uint16_t magnitude =
    sample < 0 ? static_cast<uint16_t>(-static_cast<int32_t>(sample))
               : static_cast<uint16_t>(sample);

    if (magnitude > peak)
    {
        peak = magnitude;
    }
}

bool PwmAudioSink::writeSample(int16_t sample) {
    debug_updatePeak(sample);

    if(!isPrepareCalled_) {
        return false;
    }

    const uint16_t pulse = pulseValue(sample);

    // Get the primask and turn off IRQ's to prevent a race condition with the sample update timer.
    const uint32_t primask = __get_PRIMASK();
    __disable_irq();

    if (isSampleNeeded_ && !isStopped_) {
        nextPulseValue_ = pulse;
        isSilenced_ = false;
        isSampleNeeded_ = false;
    }

    __set_PRIMASK(primask);

    return true;
}

bool PwmAudioSink::stop() {
    if(isStopped_) {
        return true;
    }

    silence();
    HAL_TIM_Base_Stop_IT(&sampleUpdateTimer_);
    HAL_TIM_PWM_Stop(&carrierTimer_, TIM_CHANNEL_1);
    isStopped_ = true;
    return true;
}

bool PwmAudioSink::silence() {
    const uint32_t primask = __get_PRIMASK();
    __disable_irq();

    isSilenced_ = true;
    nextPulseValue_ = PULSE_CENTER;

    __set_PRIMASK(primask);
    return true;
}

bool PwmAudioSink::prepare(uint32_t sampleRateHz) {
    if(sampleRateHz > MAX_SAMPLERATE_HZ || sampleRateHz == 0) {
        return false;
    }

    __HAL_TIM_SET_AUTORELOAD(
        &sampleUpdateTimer_,
        counterPeriod(sampleRateHz)
    );

    __HAL_TIM_SET_COUNTER(&sampleUpdateTimer_, 0U);
    __HAL_TIM_CLEAR_FLAG(&sampleUpdateTimer_, TIM_FLAG_UPDATE);

    sampleRateHz_ = sampleRateHz;
    isPrepareCalled_ = true;
    return true;
}

bool PwmAudioSink::start() {
    if(!isPrepareCalled_) {
        return false;
    }

    HAL_TIM_PWM_Start(&carrierTimer_, TIM_CHANNEL_1);
    HAL_TIM_Base_Start_IT(&sampleUpdateTimer_);

    isStopped_ = false;
    return true;
}

void PwmAudioSink::handleSampleInterrupt() {
        __HAL_TIM_SET_COMPARE(
            &carrierTimer_,
            TIM_CHANNEL_1,
            nextPulseValue_
            );

        isSampleNeeded_ = true;
}

uint16_t PwmAudioSink::pulseValue (int16_t sample) const {
    const int32_t scaledSample =
        static_cast<int32_t>(sample) *
        PULSE_VARIANCE /
        PCM_PEAK;

    return static_cast<uint16_t>(PULSE_CENTER + scaledSample);
}

uint16_t PwmAudioSink::counterPeriod (uint32_t sampleRateHz) const {
    uint32_t clockFreq = HAL_RCC_GetPCLK1Freq();

    RCC_ClkInitTypeDef clockConfig;
    uint32_t flashLatency;
    HAL_RCC_GetClockConfig(&clockConfig, &flashLatency);

    if (clockConfig.APB1CLKDivider != RCC_HCLK_DIV1) {
        clockFreq *= 2U;
    }

    return static_cast<uint16_t>(
        ((clockFreq + sampleRateHz / 2U) / sampleRateHz) - 1U
    );
}

