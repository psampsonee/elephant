#pragma once
#include "interrupt_handler.h"
#include "stm32f4xx_hal.h"

class i2cObject : public InterruptObject<I2C_HandleTypeDef> {
public:
    using InterruptObject::InterruptObject;
};

class i2sObject : public InterruptObject<I2S_HandleTypeDef> {
public:
    using InterruptObject::InterruptObject;
};

