#include "reset_cause.h"

resetCause getResetCause(void) {
    resetCause output;

    if (__HAL_RCC_GET_FLAG(RCC_FLAG_LPWRRST))
    {
        output = resetCause::RST_CAUSE_LOW_POWER;
    }
    else if (__HAL_RCC_GET_FLAG(RCC_FLAG_WWDGRST))
    {
        output = resetCause::RST_CAUSE_WINDOW_WATCHDOG;
    }
    else if (__HAL_RCC_GET_FLAG(RCC_FLAG_IWDGRST))
    {
        output = resetCause::RST_CAUSE_INDEP_WATCHDOG;
    }
    else if (__HAL_RCC_GET_FLAG(RCC_FLAG_SFTRST))
    {
        // This reset is induced by calling the ARM CMSIS 
        // `NVIC_SystemReset()` function!
        output = resetCause::RST_CAUSE_SOFTWARE; 
    }
    else if (__HAL_RCC_GET_FLAG(RCC_FLAG_PORRST))
    {
        output = resetCause::RST_CAUSE_PWRON_PWRDN;
    }
    else if (__HAL_RCC_GET_FLAG(RCC_FLAG_PINRST))
    {
        output = resetCause::RST_CAUSE_EXT_RST_PIN;
    }
    // Needs to come *after* checking the `RCC_FLAG_PORRST` flag in order to
    // ensure first that the reset cause is NOT a POR/PDR reset. See note
    // below. 
    else if (__HAL_RCC_GET_FLAG(RCC_FLAG_BORRST))
    {
        output = resetCause::RESET_CAUSE_BROWNOUT;
    }
    else
    {
        output = resetCause::RST_CAUSE_UNKNOWN;
    }

    // Clear all the reset flags or else they will remain set during future
    // resets until system power is fully removed.
    __HAL_RCC_CLEAR_RESET_FLAGS();

    return output;
}  