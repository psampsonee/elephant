#pragma once

#include "storage_device.h"
#include "spi_storage_base.h"
#include <cstdint>
#include <cstddef>

class SdCard : public SpiStorageBase {
public:
    SdCard(SPI_HandleTypeDef& spi, GPIO_TypeDef* csPort, uint16_t csPin)
        : SpiStorageBase(spi, csPort, csPin) {}

    bool init() override;
    ReadResult read(std::size_t block, uint8_t* buffer) override;

    bool isHighCapacity() const { return highCapacity_; }
    std::size_t getBlockSize() { return BLOCK_SIZE; }

private:
    static constexpr std::size_t BLOCK_SIZE = 512;
    bool highCapacity_ = false;

    void csLow();
    void csHigh();
    void dummyClocks();

    uint8_t waitR1();
    uint8_t command(uint8_t cmd, uint32_t arg, uint8_t crc);
    uint8_t appCommand(uint8_t cmd, uint32_t arg);
};
