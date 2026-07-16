#include "audio_player.h"
#include <cmath>
#include <cstdint>

namespace audio_test {

AudioPlayer::AudioPlayer(StorageDevice& storage, AudioSink& sink)
    : storage_(storage)
    , sink_(sink)
{
    init();
}

// Initiates audio playback for the player service to begin.
void AudioPlayer::start(uint32_t clipStartSector,
    uint32_t clipLengthSamples,
    uint16_t sampleRateHz)
{
    if (isActive()) {
        stop();
    }

    // Check if start sector is valid

    // Check if sample length is valid

    nextSectorToRead_ = clipStartSector;
    clipStartSector_ = clipStartSector;
    clipLengthSamples_ = clipLengthSamples;
    sampleRateHz_ = sampleRateHz;
    samplesPlayed_ = 0;
    samplesRemainingToRead_ = clipLengthSamples;

    state_ = State::Prepare;
}

// Main decision tree for the audio player state machine.
void AudioPlayer::service()
{
    switch (state_) {
    case State::Idle:
        // Do nothing in the Idle state.
        break;
    case State::Prepare:
        servicePrepare();
        break;
    case State::Playback:
        servicePlayback();
        break;
    case State::Underrun:
        // serviceUnderrun();
        break;
    case State::Finished:
        break;
    case State::Error:
    default:
        errorHandler();
        break;
    }
}

// Clears playback state information
void AudioPlayer::stop()
{
    // Stop playback sink from producing audio
    sink_.stop(); // Stop audio playback
    sink_.silence(); // Put playback in a safe silent state.

    // Cancel current sample playback
    spooler_.reset();

    clearPlaybackState();
    state_ = State::Idle;
}

void AudioPlayer::clearPlaybackState()
{
    // Clear bookkeeping for the current playback task
    nextSectorToRead_ = 0;
    clipStartSector_ = 0;
    clipLengthSamples_ = 0;
    sampleRateHz_ = 0;
    samplesPlayed_ = 0;
    samplesRemainingToRead_ = 0;
}

// Put the player into the playback state
void AudioPlayer::enterPlayback()
{
    state_ = State::Playback;
}

void AudioPlayer::enterUnderrun()
{
    sink_.stop();
    sink_.silence();
    state_ = State::Underrun;
}

// Put the player in the error state
void AudioPlayer::enterError()
{
    sink_.stop();
    sink_.silence();
    state_ = State::Error;
}

// Put the player in the finished state
void AudioPlayer::enterFinished()
{
    sink_.stop();
    sink_.silence();
    state_ = State::Finished;
}

void AudioPlayer::servicePrepare()
{
    // Initialize storage device
    if (!storage_.init()) {
        enterError();
        return;
    }

    // Reset spooler
    spooler_.reset();

    // For each spooler buffer:
    for (uint8_t i = 0; i < spooler_.getNumBuffers(); i++) {
        // Fill buffer with data from storage device
        if (!refillOneBuffer(i)) {
            enterError();
            return;
        }
    }

    // Initialize playback device
    if(!sink_.prepare(sampleRateHz_)) {
        enterError();
        return;
    }
    // Start playback device
    if(!sink_.start()) {
        enterError();
        return;
    }

    enterPlayback(); // The player is now ready to play. Enter the Playback state.
}

void AudioPlayer::servicePlayback()
{
    // Check if the sink needs a sample
    if (sink_.isSampleNeeded()) {
        // Check if the player has played all samples on the clip and return if so
        if (samplesPlayed_ >= clipLengthSamples_) {
            enterFinished();
            return;
        }

        int16_t sample = spooler_.nextSample();

        // Check if spooler has underrun
        if (spooler_.hasUnderrun()) {
            enterUnderrun();
            return;
        }

        // Put a sample onto the sink
        if (!sink_.writeSample(sample)) {
            enterError();
            return;
        }

        samplesPlayed_++;
    }

    // Fill any empty buffers with samples from storage
    for (uint8_t i = 0; i < spooler_.getNumBuffers(); i++) {
        if (spooler_.needsRefill(i)) {
            if (!refillOneBuffer(i)) {
                enterError();
                return;
            }
        }
    }
}

// This method fills the buffer in the spooler_ at index with data from storage_.
bool AudioPlayer::refillOneBuffer(uint8_t index)
{
    RefillBuffer buffer = spooler_.getRefillBuffer(index);

    uint16_t samplesToRead = buffer.sample_count;

    if (samplesRemainingToRead_ < samplesToRead) {
        samplesToRead = samplesRemainingToRead_;
    }

    if (samplesToRead == 0) {
        return spooler_.markRefilled(index, 0);
    }

    uint8_t* dst = reinterpret_cast<uint8_t*>(buffer.data);
    auto readResult=storage_.read(nextSectorToRead_, dst);

    if (readResult == StorageDevice::ReadResult::Error) {
        return false;
    }

    if (readResult == StorageDevice::ReadResult::NotReady) {
        return true; // no fatal error, but leave buffer needing refill
    }

    nextSectorToRead_++;
    samplesRemainingToRead_ -= samplesToRead;

    return spooler_.markRefilled(index, samplesToRead);
}

AudioPlayer::State AudioPlayer::getState() const
{
    return state_;
}

bool AudioPlayer::isPlaying() const
{
    return state_ == State::Playback;
}

bool AudioPlayer::isFinished() const
{
    return state_ == State::Finished;
}

bool AudioPlayer::isActive() const
{
    return state_ == State::Playback || state_ == State::Prepare;
}

bool AudioPlayer::hasUnderrun() const
{
    return state_ == State::Underrun;
}

void AudioPlayer::init()
{
    sink_.stop();
    sink_.silence();
    spooler_.reset();
    clearPlaybackState();
    state_ = State::Idle;
}

void AudioPlayer::errorHandler()
{
}

}
