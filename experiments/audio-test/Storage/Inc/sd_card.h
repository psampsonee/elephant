#pragma once

#include "storage_device.h"
#include "spi_storage_base.h"
#include <cstdint>
#include <cstddef>

class SdCard : public SpiStorageBase {
public:
    SdCard(SPI_HandleTypeDef& spi, GPIO_TypeDef* csPort, uint16_t csPin)
        : SpiStorageBase(SPI_HandleTypeDef& spi, GPIO_TypeDef* csPort, uint16_t csPin);

    bool init() override;
    bool read(uint32_t block, uint8_t* buffer) override;

    bool isHighCapacity() const { return highCapacity_; }

private:
    bool highCapacity_ = false;

    void csLow();
    void csHigh();
    void dummyClocks();

    uint8_t waitR1();
    uint8_t command(uint8_t cmd, uint32_t arg, uint8_t crc);
    uint8_t appCommand(uint8_t cmd, uint32_t arg);
};
