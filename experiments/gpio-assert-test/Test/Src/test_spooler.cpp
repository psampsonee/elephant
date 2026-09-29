#ifndef UNIT_TEST
#define UNIT_TEST
#endif

#include "sample_spooler.h"
#include <cassert>
#include <cstdint>
#include <cstring>
#include <iostream>

// The first sample of a freshly reset buffer should return 0, for silence.
void test_initial_state_has_no_sample()
{
    SampleSpooler spooler;
    spooler.reset();

    assert(spooler.nextSample() == 0);
}

// All samples of a freshly reset spooler should be 0, for silence.
void test_reset_clears_refill_buffers_to_zero()
{
    SampleSpooler spooler;
    RefillBuffer testBuf;

    spooler.reset();

    for (int i = 0; i < spooler.getNumBuffers(); i++) {
        testBuf = spooler.getRefillBuffer(i);
        for (int j = 0; j < testBuf.sample_count; j++) {
            assert(testBuf.data[j] == 0);
        }
    }
}

// All buffers in a freshly reset spooler should be marked for refill.
void test_initial_state_all_marked_for_refill()
{
    SampleSpooler spooler;
    spooler.reset();
    for (int i = 0; i < spooler.getNumBuffers(); i++) {
        assert(spooler.needsRefill(i) == true);
    }
}

// nextSample() should return primed samples in order, starting at index 0.
void test_primed_buffer_returns_samples_in_order()
{
    constexpr uint8_t SAMPLES_COUNT = 4;
    constexpr int16_t testData[SAMPLES_COUNT] = { 18962, 6564, 18904, 12103 };
    int16_t nextSample;

    SampleSpooler spooler;

    spooler.reset();
    RefillBuffer testBuf = spooler.getRefillBuffer(0);
    memcpy(testBuf.data, testData, sizeof(testData));
    spooler.markRefilled(0, SAMPLES_COUNT);

    for (int i = 0; i < SAMPLES_COUNT; i++) {
        nextSample = spooler.nextSample();
        assert(nextSample == testData[i]);
    }
}

// When a buffer runs out of data, it should be marked for refill.
void test_running_out_marks_for_refill()
{
    constexpr uint16_t SAMPLES_COUNT = 257;
    SampleSpooler spooler;
    RefillBuffer buffer0 = spooler.getRefillBuffer(0);

    spooler.reset();
    spooler.markRefilled(0,buffer0.sample_count);
    spooler.markRefilled(1,SAMPLES_COUNT - buffer0.sample_count);

    assert(spooler.needsRefill(0) == false);
    assert(spooler.needsRefill(1) == false);

    for (int i = 0; i < SAMPLES_COUNT; i++) {
        spooler.nextSample();
    }

    assert(spooler.needsRefill(0) == true);
    assert(spooler.needsRefill(1) == false);
}

// After all samples are consumed in buffer 0, the next sample from spooler should be at index 0 of buffer 1.
void test_wraps_to_next_buffer()
{
    constexpr int16_t MAGIC_NO = 12345;
    int16_t nextSample;

    SampleSpooler spooler;

    spooler.reset();
    RefillBuffer buffer0 = spooler.getRefillBuffer(0);
    RefillBuffer buffer1 = spooler.getRefillBuffer(1);

    buffer1.data[0] = MAGIC_NO;

    spooler.markRefilled(0, buffer0.sample_count);
    spooler.markRefilled(1, 1);

    for (int i = 0; i < buffer0.sample_count; i++) {
        spooler.nextSample();
    }

    nextSample = spooler.nextSample();

    assert(nextSample == MAGIC_NO);
}

// The samples in the second buffer should be playing in order at the "seam" bewteen buffers.
void test_preserves_order_across_buffer_boundary()
{
    constexpr int16_t MAGIC_NO[3] = { 123, 456, 789 };
    int16_t nextSample;

    SampleSpooler spooler;

    spooler.reset();
    RefillBuffer buffer0 = spooler.getRefillBuffer(0);
    RefillBuffer buffer1 = spooler.getRefillBuffer(1);

    buffer0.data[buffer0.sample_count - 1] = MAGIC_NO[0];
    buffer1.data[0] = MAGIC_NO[1];
    buffer1.data[1] = MAGIC_NO[2];

    spooler.markRefilled(0,buffer0.sample_count);
    spooler.markRefilled(1,2);

    for (int i = 0; i < buffer0.sample_count - 1; i++) {
        spooler.nextSample();
    }

    nextSample = spooler.nextSample();
    assert(nextSample == MAGIC_NO[0]);
    nextSample = spooler.nextSample();
    assert(nextSample == MAGIC_NO[1]);
    nextSample = spooler.nextSample();
    assert(nextSample == MAGIC_NO[2]);
}

// The spooler should cycle through all buffers back to the first buffer. The test writes the magic number into the first buffer after it has already played to confirm that the first buffer eventually plays again.
void test_wraps_through_all_buffers()
{
    constexpr int16_t MAGIC_NO = 2345;
    int16_t nextSample;

    SampleSpooler spooler;

    spooler.reset();
    RefillBuffer buffer0 = spooler.getRefillBuffer(0);

    uint16_t test_sample_count;
    test_sample_count = buffer0.sample_count * spooler.getNumBuffers() + 1;

    for (int i = 0; i < spooler.getNumBuffers(); i++) {
        spooler.markRefilled(i, buffer0.sample_count);
    }

    for (int i = 0; i < test_sample_count - 1; i++) {
        if (spooler.needsRefill(0)) {
            buffer0.data[0] = MAGIC_NO;
            spooler.markRefilled(0, 1);
        }
        spooler.nextSample();
    }

    nextSample = spooler.nextSample();
    assert(nextSample == MAGIC_NO);
}

// The final sample of the final buffer in the spooler should be playable. When a magic number is written to that location, it should be reached after all the other samples from all the other buffers have been consumed.
void test_reaches_final_sample_of_final_buffer()
{
    constexpr int16_t MAGIC_NO = 8765;
    int16_t nextSample;

    SampleSpooler spooler;

    spooler.reset();

    RefillBuffer bufferFinal = spooler.getRefillBuffer(
        spooler.getNumBuffers() - 1);

    bufferFinal.data[bufferFinal.sample_count-1] = MAGIC_NO;

    uint16_t test_sample_count;
    test_sample_count = bufferFinal.sample_count * spooler.getNumBuffers();

    for (int i = 0; i < spooler.getNumBuffers(); i++) {
        spooler.markRefilled(i,bufferFinal.sample_count);
    }

    for (int i = 0; i < test_sample_count - 1; i++) {
        spooler.nextSample();
    }

    nextSample = spooler.nextSample();
    assert(nextSample == MAGIC_NO);
}

// When attempting to read from a buffer that has been marked for refill, an underrun condition should be triggered.
void test_reading_buffer_that_needs_refill_sets_underrun()
{
    SampleSpooler spooler;

    spooler.reset();
    RefillBuffer buffer0 = spooler.getRefillBuffer(0);

    uint16_t test_sample_count;
    test_sample_count = buffer0.sample_count * spooler.getNumBuffers() + 1;

    for (int i = 0; i < spooler.getNumBuffers(); i++) {
        spooler.markRefilled(i,buffer0.sample_count);
    }

    for (int i = 0; i < test_sample_count - 1; i++) {
        spooler.nextSample();
    }
    assert(spooler.hasUnderrun() == false);
    spooler.nextSample();
    assert(spooler.hasUnderrun() == true);
}

// Data after the contracted number of samples should be silence (signed 0's)
void test_handles_final_partial_buffer()
{
    constexpr int16_t LAST_VALID = 2345;
    constexpr int16_t POISON = 67;
    int16_t nextSample;

    SampleSpooler spooler;

    spooler.reset();
    RefillBuffer buffer0 = spooler.getRefillBuffer(0);
    RefillBuffer buffer1 = spooler.getRefillBuffer(1);

    uint16_t valid_sample_count = buffer0.sample_count + 1;

    buffer1.data[0] = LAST_VALID;
    buffer1.data[1] = POISON;

    spooler.markRefilled(0,buffer0.sample_count);
    spooler.markRefilled(1,1); // Should be 1, as the second sample is POISON

    for (int i = 0; i < valid_sample_count - 1; i++) {
        spooler.nextSample();
    }

    nextSample = spooler.nextSample();
    assert(nextSample == LAST_VALID);

    nextSample = spooler.nextSample();
    assert(nextSample == 0);
    assert(spooler.hasUnderrun() == false);
}

int main()
{
    test_initial_state_has_no_sample();
    test_reset_clears_refill_buffers_to_zero();
    test_primed_buffer_returns_samples_in_order();
    test_running_out_marks_for_refill();
    test_wraps_to_next_buffer();
    test_preserves_order_across_buffer_boundary();
    test_wraps_through_all_buffers();
    test_reaches_final_sample_of_final_buffer();
    test_reading_buffer_that_needs_refill_sets_underrun();
    test_handles_final_partial_buffer();
    std::cout << "Tests completed without errors.";
    return 0;
}
