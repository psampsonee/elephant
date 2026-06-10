#pragma once
#include "interrupt_handler.h"
#include "stm32f4xx_hal.h"

class gpioObject : public InterruptObject<GPIO_TypeDef> {
public:
    using InterruptObject::InterruptObject;

    gpioObject() : InterruptObject() {}
    gpioObject(GPIO_TypeDef* port) : InterruptObject(port) {}

    void setPin(uint16_t pin);
    void resetPin(uint16_t pin);
    void togglePin(uint16_t pin);

    GPIO_PinState getPin(uint16_t pin);
};