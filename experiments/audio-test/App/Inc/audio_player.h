#pragma once

#include "audio_sink.h"
#include "sample_spooler.h"
#include "sample_source.h"

#include <cstdint>

struct ClipInfo {
    std::size_t startSector;
    std::size_t lengthSamples;
    uint16_t sampleRateHz;
    };

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

    AudioPlayer(SampleSource& source, AudioSink& sink);

    void start(std::size_t clipStartSector,
        std::size_t clipLengthSamples,
        uint16_t sampleRateHz); // Requests playback of a clip. deprecated implementation.
    void start(ClipInfo clip); // With clipInfo struct. Functionally identical.
    void service(); // Iterates playback
    void stop(); // Ends playback, puts PWM in silent state, clears spooler.

    State getState() const; // Returns the state of the AudioPlayer

    // External status helper functions
    bool isPlaying() const;
    bool isFinished() const;
    bool isActive() const;
    bool hasUnderrun() const;

    std::size_t samplesPlayed() const { return samplesPlayed_; }

#ifdef UNIT_TEST
    SampleSpooler& debug_getSpooler() { return spooler_; }
    const SampleSpooler& debug_getSpooler() const { return spooler_; }
    std::size_t debug_getSamplesPlayed() const { return samplesPlayed_; }
#endif

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
    //void serviceUnderrun(); // Future implementation

    // Helper functions
    bool refillOneBuffer(uint8_t index);

    void errorHandler();

    void clearPlaybackState();

    State state_;

    SampleSource& source_;
    AudioSink& sink_;
    SampleSpooler spooler_;
    ClipInfo clip_;

    std::size_t samplesRemainingToRead_;
    std::size_t samplesPlayed_;
};
