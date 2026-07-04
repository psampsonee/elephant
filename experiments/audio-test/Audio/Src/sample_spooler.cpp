// TODO: Write out control flow, what is going on, thoughts within longer functions.
#include "sample_spooler.h"

SampleSpooler::SampleSpooler()
{
    reset();
}

void SampleSpooler::reset()
{
    // Set initial states of all variables
    playBuf_ = 0;
    playPos_ = 0;
    underrun_ = false;

    for (uint8_t i = 0; i < NumBuffers; i++) {
        refillNeeded_[i] = true;
        for (uint16_t j = 0; j < SamplesPerBuffer; j++) {
            buffer_[i][j] = 0;
        }
    }
}

uint8_t SampleSpooler::getNumBuffers() const
{
    return NumBuffers;
}

bool SampleSpooler::needsRefill(uint8_t index) const
{
    if (index >= NumBuffers) {
        return false;
    }

    return refillNeeded_[index];
}

RefillBuffer SampleSpooler::getRefillBuffer(uint8_t index)
{
    if (index >= NumBuffers) {
        return { nullptr, 0 };
    }
    return { buffer_[index], SamplesPerBuffer };
}

bool SampleSpooler::markRefilled(uint8_t index, uint16_t samplesRead)
{
    if (index >= NumBuffers) {
        return false;
    }

    if (samplesRead > SamplesPerBuffer) {
        return false;
    }

    refillNeeded_[index] = false;

    padBufferWithSilence(getRefillBuffer(index), samplesRead);

    return true;
}

bool SampleSpooler::hasUnderrun() const
{
    return underrun_;
}

int16_t SampleSpooler::nextSample()
{
    // If the buffer being played from is marked for refill, the Spooler is now in underrun:
    if (refillNeeded_[playBuf_]) {
        underrun_ = true;
        return 0;
    }

    // The next sample is on the playing buffer at playPos_. Iterate playPos_:
    int16_t sample = buffer_[playBuf_][playPos_++];

    // When playPos_ reaches the end of the buffer, mark it for refill and rotate.
    if (playPos_ >= SamplesPerBuffer) {
        refillNeeded_[playBuf_] = true;
        playBuf_ = static_cast<uint8_t>((playBuf_ + 1) % NumBuffers);
        playPos_ = 0;
    }

    return sample;
}

void SampleSpooler::padBufferWithSilence(RefillBuffer buffer, uint16_t start)
{
    if (start >= SamplesPerBuffer) {
        return;
    }

    for(uint16_t i = start; i < SamplesPerBuffer; i++) {
        buffer.data[i] = 0;
    }
}
