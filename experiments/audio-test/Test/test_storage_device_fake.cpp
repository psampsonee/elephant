#include "storage_device_fake.h"
#include "storage_device_fake_test_handles.cpp"
#include <cassert>
#include <cstdint>
#include <cstring>
#include <iostream>

constexpr size_t FAKE_BLOCK = 0;
constexpr size_t BUF_SIZE = 512;

void test_read_count_increments_on_read() {
    uint8_t buffer[BUF_SIZE];

    StorageDeviceFakeTestHandles h;

    assert(h.storage.init());
    assert(h.storage.getReadCount() == 0);
    assert(h.storage.read(FAKE_BLOCK, buffer) == StorageDevice::ReadResult::Success);
    assert(h.storage.getReadCount() == 1);
    h.storage.read(FAKE_BLOCK, buffer);
    assert(h.storage.getReadCount() == 2);
}

void test_failure_functionality_init() {
    bool isStorageFailInit = false;
    StorageDeviceFakeTestHandles h({ isStorageFailInit=true });
    isStorageFailInit = !h.storage.init();
    assert(isStorageFailInit == true);
}

void test_failure_functionality_read() {
    uint8_t buffer[BUF_SIZE];
    StorageDeviceFake storage (false, true);
    auto storageReadStatus = storage.read(FAKE_BLOCK, buffer);
    assert(storageReadStatus == StorageDevice::ReadResult::Error);
}

void test_buffer_data_is_incrementing_from_zero_to_n() {
    uint8_t buffer[BUF_SIZE];

    StorageDeviceFakeTestHandles h;
    assert(h.storage.init());
    assert(h.storage.read(FAKE_BLOCK, buffer) == StorageDevice::ReadResult::Success);
    for(uint16_t i = 0; i < BUF_SIZE; i++) {
        assert(buffer[i] == static_cast<uint8_t>(i & 0xFF));
    }
}

void test_suppression_causes_read_not_ready() {
    uint8_t buffer[BUF_SIZE];
    StorageDeviceFakeTestHandles h;
    assert(h.storage.init());
    h.storage.setReady(false);
    auto storageReadStatus = h.storage.read(FAKE_BLOCK, buffer);
    assert(storageReadStatus == StorageDevice::ReadResult::NotReady);
}

int main()
{
    test_read_count_increments_on_read();
    test_failure_functionality_init();
    test_failure_functionality_read();
    test_buffer_data_is_incrementing_from_zero_to_n();
    test_suppression_causes_read_not_ready();
    std::cout << "Tests completed without errors.";
    return 0;
}
