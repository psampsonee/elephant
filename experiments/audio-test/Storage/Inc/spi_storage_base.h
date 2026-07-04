#pragma once

#include "storage_device.h"
#include <cstdint>
#include <cstddef>

class SpiStorageBase : public StorageDevice {
protected:
    SpiStorageBase(SPI_HandleTypeDef& spi, GPIO_TypeDef* csPort, uint16_t csPin)
        : spi_(&spi), csPort_(csPort), csPin_(csPin) {}

    uint8_t txrx(uint8_t data) {
        uint8_t rx = 0xFF;
        HAL_SPI_TransmitReceive(spi_, &data, &rx, 1, HAL_MAX_DELAY);
        return rx;
    }

    void csLow() {
        HAL_GPIO_WritePin(pins_.csPort, pins_.csPin, GPIO_PIN_RESET);
    }

    void csHigh() {
        HAL_GPIO_WritePin(pins_.csPort, pins_.csPin, GPIO_PIN_SET);
    }

private:
    SPI_HandleTypeDef& spi_;
    GPIO_TypeDef* csPort_;
    uint16_t csPin_;
}
