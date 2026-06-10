#pragma once
#include "sys_const.h"
#include "stm32f4xx_hal.h"

namespace sleep_test {
    void runTest(RTC_HandleTypeDef& hrtc);
    void enterStop(RTC_HandleTypeDef& hrtc);
    void leaveStop(RTC_HandleTypeDef& hrtc);
}