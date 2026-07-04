#include "audio_sink_fake.h"
#include <iostream>

bool AudioSinkFake::writeSample(int16_t sample) {
    if(fail_all_public_functions_) {
        return false;
    }

    isSilenced_ = false;
    isStopped_ = false;
    lastSampleWritten_ = sample;
    samplesWritten_++;

    return true;
}

bool AudioSinkFake::stop() {
    if(fail_all_public_functions_) {
        return false;
    }
    isStopped_ = true;

    return true;
}

bool AudioSinkFake::silence() {
    if(fail_all_public_functions_) {
        return false;
    }

    isSilenced_ = true;
    lastSampleWritten_ = 0;

    return true;
}
