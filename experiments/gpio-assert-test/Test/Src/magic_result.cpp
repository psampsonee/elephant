#include "magic_result.h"

int16_t magicResult(size_t magic) {
    size_t magicSector_lower = magic / SECTOR_SIZE_BYTES;
    size_t magicSector_upper = (magic + 1) / SECTOR_SIZE_BYTES;

    size_t magicOffset_lower = magic % SECTOR_SIZE_BYTES;
    size_t magicOffset_upper = (magic + 1) % SECTOR_SIZE_BYTES;

    int16_t magicResult_lower = static_cast<int16_t>(
        magicSector_lower * 17 + magicOffset_lower) & 0xFF;

    int16_t magicResult_upper = static_cast<int16_t>(
        magicSector_upper * 17 + magicOffset_upper) & 0xFF;

    return (magicResult_upper << 8) | magicResult_lower;
}
