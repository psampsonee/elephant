#pragma once

#include <cstdint>
#include <cstddef>

struct RefillBuffer {
    int16_t* data;
    uint16_t sample_count;
};

class SampleSpooler {
public:
    SampleSpooler();
    void reset();                                       // Sets default values

    int16_t nextSample(); // To get the next sample to play back on audio hardware

    uint8_t getNumBuffers() const;                      // gives the number of buffers available.
    bool needsRefill(uint8_t index) const;              // tells whether a particular buffer needs a refill
    RefillBuffer getRefillBuffer(uint8_t index);        // Returns a struct with a pointer of the data of the buffer to be refilled.
    bool markRefilled(uint8_t index, uint16_t samplesRead); // Sets a buffer as refilled.

    bool hasUnderrun() const;

private:
    // Class defaults
    static constexpr uint16_t SamplesPerBuffer = 256;
    static constexpr uint8_t NumBuffers = 4;

    static void padBufferWithSilence(RefillBuffer buffer, uint16_t start);

    // Buffers array
    int16_t buffer_[NumBuffers][SamplesPerBuffer];

    volatile uint8_t playBuf_;                          // Current playback buffer
    volatile uint16_t playPos_;                         // Current position in playback buffer
    volatile bool refillNeeded_[NumBuffers];            // Current Refill state of each buffer
    volatile bool underrun_;

};
