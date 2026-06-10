#include "math.h"
#include "audio_test.h"

namespace audio_test {
    void genBuffer(Audio& audioSystem, float sineFreq) {
        // Generate a sine wave with some frequency
        std::array<int16_t,audio_buffer_size*2>& buffer = audioSystem.getBufferInstance();
        for(int i = 0; i < audio_buffer_size; i++) {
            buffer[i * 2] = (int16_t) (sin(2. * M_PI * 10. * i / 2000.) * 500);
            buffer[i * 2 + 1] = (int16_t) (sin(2. * M_PI * 8. * i / 2000.) * 500);
        }
    }

    void runTest(I2C_HandleTypeDef& hi2c, DMA_HandleTypeDef& hdma_spi_tx, i2sObject& i2sObj) {
        Audio audioSys(hi2c,hdma_spi_tx,i2sObj);
        genBuffer(audioSys, 400.);
        while(1) {
            // The audio system interrupt fires when the audio buffer is empty.
            if(i2sObj.isInterruptFired())
            { 
                audioSys.play();
            }
        }
    }
}