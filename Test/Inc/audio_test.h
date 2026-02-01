#pragma once
#include "audio.h"
#include "sys_const.h"

namespace audio_test {
    using namespace std;
    //Audio audioSys;
    void genBuffer(Audio& audioSystem, float sineFreq);
    void runTest(I2C_HandleTypeDef& hi2c,
                DMA_HandleTypeDef& hdma_spi_tx,
                i2sObject& i2sObj);
}