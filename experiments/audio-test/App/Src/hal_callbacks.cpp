#include "pwm_audio_sink.h"

extern PwmAudioSink sink;

extern "C" void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef* htim)
{
    if(htim->Instance == TIM3) {
        sink.handleSampleInterrupt();
    }
}
