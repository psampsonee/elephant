#include "audio_sink_fake.h"
#include <iostream>

bool AudioSinkFake::prepare(uint16_t sampleRateHz)
{
    isPrepareCalled_ = true;
    preparedSampleRateHz_ = sampleRateHz;
    return !fail_all_public_functions_;
}

bool AudioSinkFake::start()
{
    if (!isPrepareCalled_ || fail_all_public_functions_) {
        return false;
    }

    isStarted_ = true;
    isSampleNeeded_ = true;

    return true;
}

bool AudioSinkFake::writeSample(int16_t sample)
{
    if (!isStarted_ || fail_all_public_functions_ || !isSampleNeeded_) {
        return false;
    }

    isSilenced_ = false;
    isStopped_ = false;
    lastSample_ = sample;
    samplesWritten_++;
    isSampleNeeded_ = false;

    return true;
}

bool AudioSinkFake::stop()
{
    if (!isStarted_ || fail_all_public_functions_) {
        return false;
    }
    isStopped_ = true;

    return true;
}

bool AudioSinkFake::silence()
{
    if (!isStarted_ || fail_all_public_functions_) {
        return false;
    }

    isSilenced_ = true;
    lastSample_ = 0;

    return true;
}

void AudioSinkFake::consumeSample()
{
    if (isStarted_) {
        isSampleNeeded_ = true;
    }
}
