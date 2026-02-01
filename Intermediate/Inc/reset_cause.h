#pragma once
#include "stm32f4xx_hal.h"


enum class resetCause {
    RST_CAUSE_UNKNOWN = 0,
    RST_CAUSE_LOW_POWER,
    RST_CAUSE_WINDOW_WATCHDOG,
    RST_CAUSE_INDEP_WATCHDOG,
    RST_CAUSE_SOFTWARE,
    RST_CAUSE_PWRON_PWRDN,
    RST_CAUSE_EXT_RST_PIN,
    RESET_CAUSE_BROWNOUT
};

resetCause getResetCause(void);