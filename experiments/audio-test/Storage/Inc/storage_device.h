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
    virtual ReadResult read(std::size_t block, uint8_t* buffer) = 0;
    virtual std::size_t getBlockSize() = 0;
};
