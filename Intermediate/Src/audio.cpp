#include "audio.h"


Audio::Audio(I2C_HandleTypeDef& hi2c, DMA_HandleTypeDef& hdma_spi_tx, i2sObject& i2sObj) :
            hi2c(&hi2c), hdma_spi_tx(&hdma_spi_tx), i2sObj(&i2sObj)
            {}

Audio::Audio() : hi2c(nullptr), hdma_spi_tx(nullptr), i2sObj(nullptr)
            {}

Audio::Audio(const Audio& other) :
            hi2c(other.hi2c), hdma_spi_tx(other.hdma_spi_tx), i2sObj(other.i2sObj)
            {}

Audio& Audio::operator=(const Audio& other) {
    this->hi2c = other.hi2c;
    this->hdma_spi_tx = other.hdma_spi_tx;
    this->i2sObj = other.i2sObj;
}

void Audio::play() {
    while (i2sObj->getResource().State != HAL_I2S_STATE_READY) {}
	if (HAL_I2S_Transmit_DMA(&i2sObj->getResource(), (uint16_t*) sampleBuffer.data(),
        (uint16_t) sampleBuffer.size()) != HAL_OK) {
            Error_Handler();
        }
    i2sObj->resetFlag();
}

std::array<int16_t,audio_buffer_size*nSpeakers()>& Audio::getBufferInstance() {
    return sampleBuffer;
}
