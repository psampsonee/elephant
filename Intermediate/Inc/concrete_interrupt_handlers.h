#pragma once
#include "interrupt_handler.h"
#include "stm32f4xx_hal.h"

class i2sObject : public InterruptObject<I2S_HandleTypeDef> {
public:
    using InterruptObject::InterruptObject;
};

class alarmObject : public InterruptObject<RTC_HandleTypeDef> {
public:
    using InterruptObject::InterruptObject;
};

class gpioObject : public InterruptObject<uint16_t> {
public:
    using InterruptObject::InterruptObject;
};