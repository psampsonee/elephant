#pragma once
#include "interrupt_handler.h"
#include "stm32f4xx_hal.h"

class i2sObject : public InterruptHandler {
public:

    i2sObject();
    i2sObject(I2S_HandleTypeDef& hi2s);

    void irq();
    bool isBufferEmpty();
    void resetIsBufferEmpty();

    void setI2s(I2S_HandleTypeDef& hi2s) { this->hi2s = &hi2s; }
    I2S_HandleTypeDef& getI2s() { return *(this->hi2s); } // Keep an eye on this line

    i2sObject& operator=(const i2sObject& other);

private:
    bool _isBufferEmpty;
    I2S_HandleTypeDef* hi2s;
};

class alarmObject : public InterruptHandler {
public:

    alarmObject();
    alarmObject(RTC_HandleTypeDef& hrtc) { this->hrtc = &hrtc; }

    void irq();
    bool isAlarmElapsed();
    void resetIsAlarmElapsed();

    void setrtc(RTC_HandleTypeDef& hrtc) { this->hrtc = &hrtc; }
    RTC_HandleTypeDef& getRtc() { return *(this->hrtc); }

    alarmObject& operator=(const alarmObject& other);

private:

    bool _isAlarmElapsed;
    RTC_HandleTypeDef* hrtc;
};

class gpioObject : public InterruptHandler {
public:

    gpioObject();
    gpioObject(uint16_t interruptPin) { this->_interruptPin = interruptPin; }

    void irq() { this->_interruptFlag = true; }
    bool isInterruptFired() { return this->_interruptFlag; }
    void resetFlag() { this->_interruptFlag = false; }

    void setInterruptPin(uint16_t interruptPin) { this->_interruptPin = interruptPin; }
    uint16_t getInterruptPin() { return this->_interruptPin; }

    gpioObject& operator=(const gpioObject& other);

private:

    bool _interruptFlag;
    uint16_t _interruptPin;
}