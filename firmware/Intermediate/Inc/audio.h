#pragma once
#include <array>
#include "stm32f4xx_hal.h"
#include "sys_const.h"
#include "concrete_interrupt_handlers.h"

extern void Error_Handler();

class Audio {
public:
    Audio(I2C_HandleTypeDef& hi2c,
                DMA_HandleTypeDef& hdma_spi_tx,
                i2sObject& i2sObj); // I2S_HandleTypeDef& hi2s

    Audio();

    Audio(const Audio& other);
    Audio& operator=(const Audio& other);

    void play();
    void i2sTxCompleteCallback();

    std::array<int16_t,audio_buffer_size*nSpeakers()>& getBufferInstance();

private:
    inline bool isBufferSet();

    std::array<int16_t,audio_buffer_size*nSpeakers()> sampleBuffer;

    i2sObject* i2sObj;
    DMA_HandleTypeDef* hdma_spi_tx;
    I2C_HandleTypeDef* hi2c;
};