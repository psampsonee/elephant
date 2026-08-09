#include "ADPCM_codec.h"

static_assert(sizeof(IMA_ADPCM_BLOCKHEADER) == BLOCK_HEADER_SIZE);

IMA_ADPCM_BLOCKHEADER getBlockHeader(uint8_t* block) {
    IMA_ADPCM_BLOCKHEADER value;
    std::memcpy(&value, block, sizeof(value));
    return value;
}

uint8_t code(uint8_t data, bool highPos) {
    return highPos ? (data >> 4) : (data & 0x0F);
}

int16_t sample(uint8_t code, SampleState& prev) {
    int32_t value = static_cast<int32_t>(prev.predictor);
    int8_t index = static_cast<int8_t>(std::min<uint8_t>(prev.stepIndex, 88));

    int16_t step = stepSizeTable[index];

    code &= 0x0F;

    uint16_t diffq = step >> 3;
    if ( code & 4) {
        diffq += step;
    }
    if ( code & 2) {
        diffq += step >> 1;
    }
    if ( code & 1) {
        diffq += step >> 2;
    }

    if ( code & 8) {
        value -= diffq;
    }
    else {
        value += diffq;
    }

    index += indexTable[code];

    value = std::clamp<int32_t>(value, -32768, 32767);
    index = std::clamp<int8_t>(index, 0, 88);

    prev.predictor = static_cast<int16_t>(value);
    prev.stepIndex = index;

    return static_cast<int16_t>(value);
}
