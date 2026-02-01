#pragma once
#include "reset_cause.h"
#include "interrupt_handler.h"
#include "stm32f4xx_hal.h"
#include <array>

extern void Error_Handler();

class rtcObject : public InterruptObject<RTC_HandleTypeDef> {
public:
    using InterruptObject::InterruptObject;

    rtcObject(RTC_HandleTypeDef& resource, resetCause* myResetCause) :
        InterruptObject(resource), _myResetCause(myResetCause) {
            handleResetCause();
        }

    void irq();

    RTC_TimeTypeDef getTime();
    RTC_DateTypeDef getDate();

    void setTime(RTC_TimeTypeDef time);
    void setDate(RTC_DateTypeDef date);
    void setAlarm(uint32_t deltaSeconds);

    void resetFlag() { __HAL_RTC_WAKEUPTIMER_CLEAR_FLAG(_resource, RTC_FLAG_ALRAF); }
private:
    resetCause* _myResetCause;

    void handleResetCause();
    RTC_AlarmTypeDef alarmIn(uint32_t deltaSeconds) ;
};