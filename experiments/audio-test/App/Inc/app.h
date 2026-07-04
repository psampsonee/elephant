#pragma once
#include "main.h"
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
    SPI_HandleTypeDef* spi1;
    // I2C_HandleTypeDef* i2c1;
    // I2S_HandleTypeDef* i2s2;

    // DMA_HandleTypeDef* dma_spi_tx;

    GPIO_TypeDef* sd_cs_port;
    uint16_t sd_cs_pin;
} AppHandles;

void app_main(AppHandles* handles);

#ifdef __cplusplus
}
#endif
