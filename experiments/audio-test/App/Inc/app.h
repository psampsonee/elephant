#pragma once

#include "stm32f4xx_hal.h"
#include "stm32f4xx.h"

#ifdef __cplusplus
extern "C" {
#endif
    static constexpr uint16_t SAMPLE_RATE_HZ = 48000;
    static constexpr uint16_t PCM_PEAK = 32768;
    static constexpr uint32_t CLIP_LENGTH_SAMPLES = 109593;
    static constexpr uint16_t CLIP_START_SECTOR = 2048;

void app_main();

#ifdef __cplusplus
}
#endif
