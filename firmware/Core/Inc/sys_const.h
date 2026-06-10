#pragma once
#include <cstdint>

const bool is_audio_stereo = true;

// The number of speakers that the system has, depending on if it's stereo
constexpr uint8_t nSpeakers() {
    return (is_audio_stereo) ? 2 : 1;
}

const int audio_buffer_kb = 8; // kilobytes
const int audio_buffer_size = audio_buffer_kb * 1024; // bytes
const float sampling_frequency = 96000;
const int uint16_max = 65535;