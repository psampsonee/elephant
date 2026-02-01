#include "rtcObject.h"

void rtcObject::irq() {
    setFlag();
}

void rtcObject::handleResetCause() {
    switch(*(this->_myResetCause)) {
        case resetCause::RST_CAUSE_SOFTWARE:
            break;
        case resetCause::RST_CAUSE_LOW_POWER:
        case resetCause::RST_CAUSE_WINDOW_WATCHDOG:
        case resetCause::RST_CAUSE_INDEP_WATCHDOG:
        case resetCause::RST_CAUSE_EXT_RST_PIN:
        case resetCause::RESET_CAUSE_BROWNOUT:
        case resetCause::RST_CAUSE_PWRON_PWRDN:
        default:
            break;
    }
}

void rtcObject::setAlarm(uint32_t deltaSeconds) {
    RTC_AlarmTypeDef sAlarm = alarmIn(deltaSeconds);

    sAlarm.AlarmTime.SubSeconds = 0x0;
    sAlarm.AlarmTime.DayLightSaving = RTC_DAYLIGHTSAVING_NONE;
    sAlarm.AlarmTime.StoreOperation = RTC_STOREOPERATION_RESET;
    sAlarm.AlarmMask = RTC_ALARMMASK_DATEWEEKDAY|RTC_ALARMMASK_HOURS
                            |RTC_ALARMMASK_MINUTES;
    sAlarm.AlarmSubSecondMask = RTC_ALARMSUBSECONDMASK_ALL;
    sAlarm.AlarmDateWeekDaySel = RTC_ALARMDATEWEEKDAYSEL_DATE;
    sAlarm.AlarmDateWeekDay = 0x1;
    sAlarm.Alarm = RTC_ALARM_A;
    if (HAL_RTC_SetAlarm_IT(this->_resource, &sAlarm, RTC_FORMAT_BCD) != HAL_OK)
    {
        Error_Handler();
    }
}

RTC_AlarmTypeDef rtcObject::alarmIn(uint32_t deltaSeconds) {
    using std::array;

    const int N_TIME_UNITS = 3;
    RTC_AlarmTypeDef output = {0};
    float divisor;
    uint32_t remainder = deltaSeconds;

    array<const uint8_t, N_TIME_UNITS - 1> TIME_PERIOD_CONVERSIONS = {60, 60};
    array<uint8_t* , N_TIME_UNITS> deltaPeriods = {&(output.AlarmTime.Hours),
        &(output.AlarmTime.Minutes), &(output.AlarmTime.Seconds)};


    for(uint8_t i = 0; i < N_TIME_UNITS; i++) {
        divisor = 1;
        for(uint8_t j = 0; j < N_TIME_UNITS - 1 - i; j++) {
            divisor *= TIME_PERIOD_CONVERSIONS[j];
        }
        *(deltaPeriods[i]) = int(remainder/divisor);
        remainder = int(remainder % (int)divisor);
    }   
    return output;
}