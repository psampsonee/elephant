#pragma once
constexpr size_t INITIAL_SECTOR = 0;
constexpr size_t SECTOR_SIZE_SAMPLES = 256;
constexpr size_t BUF_SIZE_SAMPLES = 4*SECTOR_SIZE_SAMPLES;
constexpr size_t SECTOR_SIZE_BYTES = SECTOR_SIZE_SAMPLES*sizeof(int16_t);
