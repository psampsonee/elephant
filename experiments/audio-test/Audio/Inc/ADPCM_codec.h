#pragma once
#include <algorithm>
#include <cstdint>
#include <cstring>
#include <iostream>
#include "sample_source.h"

static constexpr size_t BLOCK_SIZE = 1024;
static constexpr size_t BLOCK_HEADER_SIZE = 4;
static constexpr size_t BLOCK_SAMPLE_COUNT =
    1 + (BLOCK_SIZE - BLOCK_HEADER_SIZE) * 2;

typedef struct ima_adpcm_blockheader {
 int16_t iSample;           // Initial sample
 uint8_t iIndex;            // Initial index
 uint8_t reserved;          // Unused.
} IMA_ADPCM_BLOCKHEADER;

struct decompressed_pcm_block {
    int16_t* samples;
    size_t sampleCount = BLOCK_SAMPLE_COUNT;
};

struct SampleState {
    int16_t predictor;
    int8_t stepIndex;
    size_t compressedOffset;
};

/* Table of index changes */
static constexpr int8_t indexTable[16] = {
 -1, -1, -1, -1, 2, 4, 6, 8,
 -1, -1, -1, -1, 2, 4, 6, 8,
};

/* Quantizer step size lookup table */
static constexpr int16_t stepSizeTable[89] = {
 7, 8, 9, 10, 11, 12, 13, 14, 16, 17,
 19, 21, 23, 25, 28, 31, 34, 37, 41, 45,
 50, 55, 60, 66, 73, 80, 88, 97, 107, 118,
 130, 143, 157, 173, 190, 209, 230, 253, 279, 307,
 337, 371, 408, 449, 494, 544, 598, 658, 724, 796,
 876, 963, 1060, 1166, 1282, 1411, 1552, 1707, 1878, 2066,
 2272, 2499, 2749, 3024, 3327, 3660, 4026, 4428, 4871, 5358,
 5894, 6484, 7132, 7845, 8630, 9493, 10442, 11487, 12635, 13899,
 15289, 16818, 18500, 20350, 22385, 24623, 27086, 29794, 32767
};

// Helper functions
IMA_ADPCM_BLOCKHEADER getBlockHeader(uint8_t* block);

uint8_t code(uint8_t data, bool highPos);

int16_t sample(uint8_t code, SampleState& prev);
