#include "gpioObject.h"

void gpioObject::setPin(uint16_t pin) {  
    HAL_GPIO_WritePin(this->_resource, pin, GPIO_PIN_SET);
}

void gpioObject::resetPin(uint16_t pin) {  
    HAL_GPIO_WritePin(this->_resource, pin, GPIO_PIN_RESET);
}

void gpioObject::togglePin(uint16_t pin) {
    HAL_GPIO_TogglePin(this->_resource, pin);
}

GPIO_PinState gpioObject::getPin(uint16_t pin) {
    return HAL_GPIO_ReadPin(this->_resource,pin);
}