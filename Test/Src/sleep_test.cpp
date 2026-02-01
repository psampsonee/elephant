#include "sleep_test.h"

namespace sleep_test {
    void runTest(RTC_HandleTypeDef& hrtc) {
        while (1) {
            enterStop(hrtc);
            leaveStop();
        }
    }

    void enterStop(RTC_HandleTypeDef& hrtc) {
    __HAL_PWR_CLEAR_FLAG(PWR_FLAG_WU);
    __HAL_RTC_WAKEUPTIMER_CLEAR_FLAG(&hrtc, RTC_FLAG_WUTF);
    HAL_SuspendTick();
    HAL_PWR_EnterSTOPMode(PWR_LOWPOWERREGULATOR_ON, PWR_STOPENTRY_WFI);
    }

    void leaveStop() {
        //SysTick_Config();
	    HAL_ResumeTick();
    }
}