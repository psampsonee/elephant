#pragma once
#include <cstdint>
#include <cstddef>

enum class ReadResult {
    Success,
    NotReady,
    Error
};

class StorageDevice {
public:
    virtual bool init() = 0;
    virtual ReadResult read(std::size_t block, uint8_t* buffer) = 0;
    virtual std::size_t getSectorSize() = 0;
};
