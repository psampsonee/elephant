#pragma once
#include "audio_sink.h"
#include <cstdint>

class PwmAudioSink : public AudioSink{
public:
    bool writeSample(int16_t sample) override;
    bool stop() override;
    bool silence() override;
};
