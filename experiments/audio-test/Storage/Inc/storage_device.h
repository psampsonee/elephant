#pragma once
#include <cstdint>
#include <cstddef>

class StorageDevice {
public:
    virtual bool init() = 0;
    virtual bool read(uint32_t block, uint8_t* buffer) = 0;
};
