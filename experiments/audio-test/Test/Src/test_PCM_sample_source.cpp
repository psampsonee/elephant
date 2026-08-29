#ifndef UNIT_TEST
#define UNIT_TEST
#endif
#include "storage_device_fake.h"
#include "PCM_sample_source.h"
#include "sector_test.h"
#include "PCM_sample_source_test_handles.h"
#include "magic_result.cpp"
#include <cassert>
#include <cstdint>
#include <cstring>
#include <iostream>

constexpr size_t magic = 26;

void test_source_init() {
    PCMSampleSourceTestHandles h;
    assert(h.source.init());
}

void test_source_start_writes_workspace() {
    PCMSampleSourceTestHandles h;
    h.source.init();
    h.source.start(INITIAL_SECTOR);
    assert(h.source.getWorkspaceSample_debug(magic/sizeof(int16_t)) == magicResult(magic));
}

void test_getSamples_returns_workspace_data() {
    constexpr size_t magic = 26;

    int16_t buffer[BUF_SIZE_SAMPLES];

    PCMSampleSourceTestHandles h;
    h.source.init();
    h.source.start(INITIAL_SECTOR);
    assert(h.source.getSamples(buffer,SECTOR_SIZE_SAMPLES));
    assert(buffer[magic/sizeof(int16_t)] == magicResult(magic));
}

void test_getSamples_sector_seam() {
    int16_t buffer[BUF_SIZE_SAMPLES];

    PCMSampleSourceTestHandles h;
    h.source.init();
    h.source.start(INITIAL_SECTOR);
    assert(h.source.getSamples(buffer,SECTOR_SIZE_SAMPLES*2));
    for (size_t i = 0; i < 2; i++) {
        size_t magic = (SECTOR_SIZE_BYTES-2)+(i*2);
        assert(buffer[magic/sizeof(int16_t)] == magicResult(magic));
    }
}

void test_start_storage_failure_returns_false() {
    PCMSampleSourceTestHandles h({ .storageFailRead=true });
    h.source.init();
    assert(h.source.start(INITIAL_SECTOR) == false);
}

void test_getSamples_storage_failure_returns_false() {
    int16_t buffer[BUF_SIZE_SAMPLES];

    PCMSampleSourceTestHandles h;
    h.source.init();
    h.source.start(INITIAL_SECTOR);
    h.storage.setFailRead(true);
    assert(h.source.getSamples(buffer,BUF_SIZE_SAMPLES) == false);
}

void test_getSamples_returns_arbitrary_count() {
    constexpr size_t TEST_IT = 4;
    constexpr size_t TEST_SAMPLE_COUNTS[TEST_IT] = {11, 50, 300, 700};
    constexpr int16_t SENTINEL = 0x5555;

    int16_t buffer[BUF_SIZE_SAMPLES];

    PCMSampleSourceTestHandles h;
    h.source.init();
    for(size_t i = 0; i < TEST_IT; i++) {
        size_t testSampleCount = TEST_SAMPLE_COUNTS[i];
        h.source.start(INITIAL_SECTOR);
        std::fill(std::begin(buffer), std::end(buffer), SENTINEL);
        assert(h.source.getSamples(buffer,testSampleCount));
        assert(buffer[testSampleCount-1] ==
            magicResult((testSampleCount-1)*2));
        assert(buffer[testSampleCount] == SENTINEL);
        h.source.reset();
    }
}

void test_getSamples_past_sector_count_fails() {
    constexpr size_t SECTOR_COUNT = 2;
    int16_t buffer[BUF_SIZE_SAMPLES];

    PCMSampleSourceTestHandles h({ .sectorCount=SECTOR_COUNT });
    h.source.init();
    h.source.start(INITIAL_SECTOR);
    assert(h.source.getSamples(buffer,SECTOR_SIZE_SAMPLES*SECTOR_COUNT) == true);
    assert(h.source.getSamples(buffer,1) == false);
}

void test_getSamples_without_start_fails() {
    int16_t buffer[BUF_SIZE_SAMPLES];

    PCMSampleSourceTestHandles h;
    h.source.init();
    assert(h.source.getSamples(buffer,BUF_SIZE_SAMPLES) == false);
}

void test_reset_sets_workspace_index_variables_to_0() {
    int16_t buffer[BUF_SIZE_SAMPLES];

    PCMSampleSourceTestHandles h;
    h.source.init();
    h.source.start(2);
    assert(h.source.debug_getWorkspaceSectorOffset() == 2);
    h.source.getSamples(buffer,1);
    assert(h.source.debug_getWorkspaceIndex() != 0);
    h.source.reset();
    assert(h.source.debug_getWorkspaceIndex() == 0);
    assert(h.source.debug_getWorkspaceSectorOffset() == 0);
}

void test_getSamples_always_writes_buffer_at_index_0() {
    int16_t buffer[BUF_SIZE_SAMPLES];

    PCMSampleSourceTestHandles h;
    h.source.init();
    h.source.start(INITIAL_SECTOR);
    h.source.getSamples(buffer,1);
    h.source.getSamples(buffer,1);
    assert(buffer[0] == magicResult(2));
}

int main()
{
    test_source_init();
    test_source_start_writes_workspace();
    test_getSamples_returns_workspace_data();
    test_getSamples_sector_seam();
    test_start_storage_failure_returns_false();
    test_getSamples_storage_failure_returns_false();
    test_getSamples_returns_arbitrary_count();
    test_getSamples_past_sector_count_fails();
    test_getSamples_without_start_fails();
    test_reset_sets_workspace_index_variables_to_0();
    test_getSamples_always_writes_buffer_at_index_0();
    std::cout << "Tests completed without errors.";
    return 0;
}
