#include "sleep_test.h"

namespace sleep_test {
    void runTest(RTC_HandleTypeDef& hrtc) {
        while (1) {                                                                                 
            enterStop(hrtc);
            leaveStop(hrtc);
            HAL_Delay(500);
        }
    }

    void enterStop(RTC_HandleTypeDef& hrtc) {
    __HAL_RTC_WAKEUPTIMER_CLEAR_FLAG(&hrtc, RTC_FLAG_ALRAF);
    HAL_SuspendTick();
    HAL_PWR_EnterSTOPMode(PWR_LOWPOWERREGULATOR_ON, PWR_STOPENTRY_WFI);
    }

    void leaveStop(RTC_HandleTypeDef& hrtc) {
	    HAL_ResumeTick();
        if ( SysTick_Config(SystemCoreClock / 1000) != 0) {

        } 
    }
}