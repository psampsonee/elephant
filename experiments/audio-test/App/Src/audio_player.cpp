#include "audio_player.h"
#include <cmath>
#include <cstdint>

AudioPlayer::AudioPlayer(StorageDevice& storage, AudioSink& sink)
    : storage_(storage)
    , sink_(sink)
{
    init();
}

void AudioPlayer::start(std::size_t clipStartSector,
        std::size_t clipLengthSamples,
        uint16_t sampleRateHz) {

    start(ClipInfo{clipStartSector,
        clipLengthSamples,
        sampleRateHz});
}

// Initiates audio playback for the player service to begin.
void AudioPlayer::start(ClipInfo clip)
{
    if (isActive()) {
        stop();
    }

    // Check if start sector is valid

    // Check if sample length is valid

    clip_ = clip;
    source_.start(clip_.startSector);

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
    source.reset();

    // Clear bookkeeping for the current playback task
    clip_.StartSector = 0;
    clip_.LengthSamples = 0;
    clip_.sampleRateHz = 0;
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
    // Initialize source
    if (!source_.init()) {
        enterError();
        return;
    }

    // Reset spooler
    spooler_.reset();

    // For each spooler buffer:
    for (uint8_t i = 0; i < spooler_.getNumBuffers(); i++) {
        // Fill buffer with data from sample source
        if (!refillOneBuffer(i)) {
            enterError();
            return;
        }
    }

    // Initialize playback device
    if(!sink_.prepare(clip_.sampleRateHz)) {
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
        if (samplesPlayed_ >= clip_.lengthSamples) {
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

    size_t samplesToRead = buffer.sample_count;

    if (samplesRemainingToRead_ < samplesToRead) {
        samplesToRead = samplesRemainingToRead_;
    }

    if (samplesToRead == 0) {
        return spooler_.markRefilled(index, 0);
    }

    if (!source_.getSamples(buffer.data, samplesToRead)) {
        return false;
    }

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
