#ifndef UNIT_TEST
#define UNIT_TEST
#endif
#include "storage_device_fake.h"
#include "ADPCM_sample_source.h"
#include "ADPCM_sample_source_test_handles.h"
#include "fake_adpcm_data.h"
#include "fake_decoded_pcm_data.h"
#include <cassert>
#include <cstdint>
#include <cstring>
#include <iostream>

constexpr size_t magic = 26;

void test_source_init() {
    ADPCMSampleSourceTestHandles h;
    assert(h.source.init());
}

void test_source_start_writes_workspace() {
    ADPCMSampleSourceTestHandles h;
    h.source.init();
    h.setStorageData(fake_adpcm_data, fake_adpcm_byte_count);
    h.source.start(INITIAL_SECTOR);
    assert(h.source.debug_getWorkspaceSample(magic) == fake_decoded_pcm_data[magic]);
}

void test_getSamples_returns_workspace_data() {
    int16_t buffer[BUF_SIZE_SAMPLES];

    ADPCMSampleSourceTestHandles h;
    h.source.init();
    h.setStorageData(fake_adpcm_data, fake_adpcm_byte_count);
    h.source.start(INITIAL_SECTOR);
    assert(h.source.getSamples(buffer,ima_adpcm::FRAME_SAMPLE_COUNT*2));
    assert(buffer[magic] == fake_decoded_pcm_data[magic]);
}

void test_getSamples_returns_correct_decoded_pcm() {
    int16_t buffer[BUF_SIZE_SAMPLES];

    ADPCMSampleSourceTestHandles h;
    h.source.init();
    h.setStorageData(fake_adpcm_data, fake_adpcm_byte_count);
    h.source.start(INITIAL_SECTOR);
    assert(h.source.getSamples(buffer,fake_decoded_pcm_data_sample_count));
    for(size_t i = 0; i < fake_decoded_pcm_data_sample_count; i++) {
        assert(buffer[i] == fake_decoded_pcm_data[i]);
    }
}

void test_start_storage_failure_returns_false() {
    ADPCMSampleSourceTestHandles h({ .storageFailRead=true });
    h.source.init();
    assert(h.source.start(INITIAL_SECTOR) == false);
}

void test_getSamples_storage_failure_returns_false() {
    int16_t buffer[BUF_SIZE_SAMPLES];

    ADPCMSampleSourceTestHandles h;
    h.source.init();
    h.source.start(INITIAL_SECTOR);
    h.storage.setFailRead(true);
    assert(h.source.getSamples(buffer,BUF_SIZE_SAMPLES) == false);
}

void test_getSamples_returns_arbitrary_count() {
    constexpr size_t TEST_IT = 4;
    constexpr size_t TEST_SAMPLE_COUNTS[TEST_IT] = {11, 50, 307, 2401};
    constexpr int16_t SENTINEL = 0x5555;

    int16_t buffer[BUF_SIZE_SAMPLES];

    ADPCMSampleSourceTestHandles h;
    h.source.init();
    for(size_t i = 0; i < TEST_IT; i++) {
        size_t testSampleCount = TEST_SAMPLE_COUNTS[i];
        h.setStorageData(fake_adpcm_data, fake_adpcm_byte_count);
        h.source.start(INITIAL_SECTOR);
        std::fill(std::begin(buffer), std::end(buffer), SENTINEL);
        assert(h.source.getSamples(buffer,testSampleCount));
        assert(buffer[testSampleCount-1] == fake_decoded_pcm_data[testSampleCount-1]);
        assert(buffer[testSampleCount] == SENTINEL);
        h.source.reset();
    }
}

void test_getSamples_without_start_fails() {
    int16_t buffer[BUF_SIZE_SAMPLES];

    ADPCMSampleSourceTestHandles h;
    h.source.init();
    assert(h.source.getSamples(buffer,BUF_SIZE_SAMPLES) == false);
}

void test_reset_sets_workspace_index_variables_to_0() {
    int16_t buffer[BUF_SIZE_SAMPLES];

    ADPCMSampleSourceTestHandles h;
    h.source.init();
    h.source.start(2);
    assert(h.source.debug_getCompressedBufferSectorOffset() != 0);
    h.source.getSamples(buffer,1);
    assert(h.source.debug_getWorkspaceIndex() != 0);
    h.source.reset();
    assert(h.source.debug_getWorkspaceIndex() == 0);
    assert(h.source.debug_getCompressedBufferSectorOffset() == 0);
}

void test_getSamples_always_writes_buffer_at_index_0() {
    int16_t buffer[BUF_SIZE_SAMPLES];

    ADPCMSampleSourceTestHandles h;
    h.source.init();
    h.setStorageData(fake_adpcm_data, fake_adpcm_byte_count);
    h.source.start(INITIAL_SECTOR);
    h.source.getSamples(buffer,4);
    h.source.getSamples(buffer,4);
    assert(buffer[0] == fake_decoded_pcm_data[4]);
}

int main()
{
    test_source_init();
    test_source_start_writes_workspace();
    test_getSamples_returns_workspace_data();
    test_getSamples_returns_correct_decoded_pcm();
    test_start_storage_failure_returns_false();
    test_getSamples_storage_failure_returns_false();
    test_getSamples_returns_arbitrary_count();
    test_getSamples_without_start_fails();
    test_reset_sets_workspace_index_variables_to_0();
    test_getSamples_always_writes_buffer_at_index_0();
    std::cout << "Tests completed without errors.";
    return 0;
}
