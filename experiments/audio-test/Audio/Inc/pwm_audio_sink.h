#pragma once
#include "audio_sink.h"
#include <cstdint>

class PwmAudioSink : public AudioSink{
public:
    void writeSample(int16_t sample) override;
    void stop() override;
    void silence() override;
};
