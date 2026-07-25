#pragma once

#include "audio_sink.h"
#include "sample_spooler.h"
#include "storage_device.h"

#include <cstdint>

struct AppHandles;

// Internal class states
class AudioPlayer {
public:
    enum class State : uint8_t {
        Idle,
        Prepare,
        Playback,
        Underrun,
        Finished,
        Error
    };

    AudioPlayer(StorageDevice& storage, AudioSink& sink);

    void start(uint32_t clipStartSector,
        uint32_t clipLengthSamples,
        uint16_t sampleRateHz); // Requests playback of a clip. buffers.
    void service(); // Iterates playback
    void stop(); // Ends playback, puts PWM in silent state, clears spooler.

    State getState() const; // Returns the state of the AudioPlayer

    // External status helper functions
    bool isPlaying() const;
    bool isFinished() const;
    bool isActive() const;
    bool hasUnderrun() const;

    uint32_t samplesPlayed() const { return samplesPlayed_; }

    SampleSpooler& debug_getSpooler() { return spooler_; }
    const SampleSpooler& debug_getSpooler() const { return spooler_; }
    uint32_t debug_getSamplesPlayed() const { return samplesPlayed_; }

private:
    void init(); // Initializes player to silent Idle state.

    // State transition handler functions
    void enterPlayback();
    void enterUnderrun();
    void enterError();
    void enterFinished();

    // Service functions for the service loop
    void servicePrepare();
    void servicePlayback();

    // Helper functions
    bool refillOneBuffer(uint8_t index);

    void errorHandler();

    void clearPlaybackState();

    State state_;

    StorageDevice& storage_;
    AudioSink& sink_;
    SampleSpooler spooler_;

    uint32_t nextSectorToRead_;
    uint32_t clipStartSector_;
    uint32_t clipLengthSamples_;
    uint16_t sampleRateHz_;
    uint32_t samplesRemainingToRead_;
    uint32_t samplesPlayed_;
};
