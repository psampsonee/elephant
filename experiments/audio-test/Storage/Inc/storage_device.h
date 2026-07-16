#pragma once
#include <cstdint>
#include <cstddef>

class StorageDevice {
public:
    enum class ReadResult {
        Success,
        NotReady,
        Error
    };

    virtual bool init() = 0;
    virtual ReadResult read(uint32_t block, uint8_t* buffer) = 0;
};
