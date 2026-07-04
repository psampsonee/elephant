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

    void start(uint32_t sample_count);                  // Prepares audio playback by resetting internal variables and preparing for refill.

    void beginPlayback(); // sets state to Playing.

    int16_t nextSampleISR(); // To get the next sample to play back on audio hardware

    uint8_t getNumBuffers() const;                      // gives the number of buffers available.
    bool needsRefill(uint8_t index) const;              // tells whether a particular buffer needs a refill
    RefillBuffer getRefillBuffer(uint8_t index);        // Returns a struct with a pointer of the data of the buffer to be refilled.
    void markRefilled(uint8_t index);                   // Sets a buffer as refilled.

    // External status helper functions
    bool isPlaying() const;
    bool isFinished() const;
    bool hasUnderrun() const;

private:
    //Internal class states
    enum class State : uint8_t {
        Idle,
        Priming,
        Playing,
        Underrun,
        Finished,
        Error
    };

    // Class defaults
    static constexpr uint16_t SamplesPerBuffer = 256;
    static constexpr uint8_t NumBuffers = 4;

    // Buffers array
    int16_t buffer_[NumBuffers][SamplesPerBuffer];

    volatile uint8_t playBuf_;                          // Current playback buffer
    volatile uint16_t playPos_;                         // Current position in playback buffer
    volatile bool refillNeeded_[NumBuffers];            // Current Refill state of each buffer
    volatile uint32_t samplesLeft_; // Number of samples left in the buffer
    volatile bool underrun_;
    volatile State state_;                         // Current Internal class state
};
