#include "storage_device_fake.h"
#include <cassert>
#include <cstdint>
#include <cstring>
#include <iostream>

constexpr uint32_t FAKE_BLOCK = 0xFF000000;
constexpr uint16_t BUF_SIZE = 512;

void test_read_count_increments_on_read() {
    uint8_t buffer[BUF_SIZE];

    StorageDeviceFake storage;
    storage.init();
    assert(storage.getReadCount() == 0);
    storage.read(FAKE_BLOCK, buffer);
    assert(storage.getReadCount() == 1);
    storage.read(FAKE_BLOCK, buffer);
    assert(storage.getReadCount() == 2);
}

void test_failure_functionality_init() {
    bool isStorageFailInit = false;
    StorageDeviceFake storage (true, false);
    isStorageFailInit = !storage.init();
    assert(isStorageFailInit == true);
}

void test_failure_functionality_read() {
    uint8_t buffer[BUF_SIZE];
    bool isStorageFailRead = false;
    StorageDeviceFake storage (false, true);
    isStorageFailRead = !storage.read(FAKE_BLOCK, buffer);
    assert(isStorageFailRead == true);
}

void test_buffer_data_is_incrementing_from_zero_to_BUF_SIZE() {
    uint8_t buffer[BUF_SIZE];

    StorageDeviceFake storage;
    storage.init();
    storage.read(FAKE_BLOCK, buffer);
    for(uint16_t i = 0; i < BUF_SIZE; i++) {
        assert(buffer[i] == static_cast<uint8_t>(i));
    }
}

int main()
{
    test_read_count_increments_on_read();
    test_failure_functionality_init();
    test_failure_functionality_read();
    test_buffer_data_is_incrementing_from_zero_to_BUF_SIZE();
    std::cout << "Tests completed without errors.";
    return 0;
}
