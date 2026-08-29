#ifndef UNIT_TEST
#define UNIT_TEST
#endif

#include <cassert>
#include <cstdint>
#include <cstring>
#include <iostream>
#include "audio_player.h"
#include "ADPCM_sample_source.h"
#include "sample_spooler.h"
#include "audio_sink_fake.h"
#include "storage_device_fake.h"
#include "sector_test.h"
#include "magic_result.h"
#include "storage_device_fake_test_handles.h"
#include "fake_adpcm_data.h"
#include "fake_decoded_pcm_data.h"

static constexpr uint32_t FAKE_BLOCK = 0xFF000000;
static constexpr uint16_t BUF_SIZE = 512;

static constexpr uint16_t CLIP_LENGTH_SAMPLES = 1000;
static constexpr uint16_t SAMPLE_RATE_HZ = 8000;

struct AudioPlayerTestConfig {
    bool storageFailInit = false;
    bool storageFailRead = false;
    bool storagePreloadData = true;
    bool sinkFailPrepare = false;
    size_t blockCount = BLOCK_COUNT;
    size_t sampleCount = CLIP_LENGTH_SAMPLES;
};

struct AudioPlayerTestHandles {
    StorageDeviceFake storage;
    ADPCMSampleSource source;
    AudioSinkFake sink;
    AudioPlayer player;

    AudioPlayerTestHandles(AudioPlayerTestConfig cfg = { })
        : storage(
            cfg.storageFailInit,
            cfg.storageFailRead,
            cfg.blockCount,
            cfg.sampleCount,
            cfg.storagePreloadData)
        , source(storage)
        , sink(cfg.sinkFailPrepare)
        , player(source, sink)
    {}

    void setStorageData(const uint8_t* data, size_t size) {
        auto& storageData = storage.getStorageData();
        std::memcpy(storageData.data, data, size);
    }

    AudioPlayerTestHandles(const AudioPlayerTestHandles&) = delete;
    AudioPlayerTestHandles& operator=(const AudioPlayerTestHandles&) = delete;
};

void test_initial_state_is_idle()
{
    AudioPlayerTestHandles h;

    assert(h.player.getState() == AudioPlayer::State::Idle);
}

void test_start_enters_prepare_without_touching_sink()
{
    AudioPlayerTestHandles h;

    h.player.start(0, CLIP_LENGTH_SAMPLES, SAMPLE_RATE_HZ);

    assert(h.player.getState() == AudioPlayer::State::Prepare);
    assert(h.sink.isPrepareCalled() == false);
}

void test_service_prepare_calls_sink_prepare()
{
    AudioPlayerTestHandles h;
    h.player.start(0, CLIP_LENGTH_SAMPLES, SAMPLE_RATE_HZ);
    h.player.service();
    assert(h.player.getState() != AudioPlayer::State::Error);
    assert(h.sink.isPrepareCalled() == true);
}

void test_successful_prepare_enters_playback()
{
    AudioPlayerTestHandles h;
    h.player.start(0, CLIP_LENGTH_SAMPLES, SAMPLE_RATE_HZ);
    h.player.service();
    assert(h.player.isPlaying());
    assert(h.player.getState() == AudioPlayer::State::Playback);
}

void test_start_while_playing_stops_current_playback_first()
{
    AudioPlayerTestHandles h;
    h.player.start(0, CLIP_LENGTH_SAMPLES, SAMPLE_RATE_HZ);
    h.player.service();
    assert(h.player.isPlaying());
    h.player.start(0, CLIP_LENGTH_SAMPLES, SAMPLE_RATE_HZ);
    assert(h.player.getState() == AudioPlayer::State::Prepare);
}

void test_start_from_finished_enters_prepare_without_stopping()
{
    AudioPlayerTestHandles h;
    h.player.start(0, 1, SAMPLE_RATE_HZ);
    h.player.service(); // first service() completes servicePrepare.
    h.player.service();
    h.sink.consumeSample();
    h.player.service();
    h.player.start(0, 1, SAMPLE_RATE_HZ);
    assert(h.player.getState() == AudioPlayer::State::Prepare);
}

void test_service_playback_consumes_samples()
{
    AudioPlayerTestHandles h;
    h.player.start(0, CLIP_LENGTH_SAMPLES, SAMPLE_RATE_HZ);
    assert(h.sink.samplesWritten() == 0);

}

void test_samples_played_equals_samples_written()
{
    assert(CLIP_LENGTH_SAMPLES >= 6);
    AudioPlayerTestHandles h;
    h.player.start(0, CLIP_LENGTH_SAMPLES, SAMPLE_RATE_HZ);
    assert(h.player.samplesPlayed() == h.sink.samplesWritten());
    h.player.service(); // first service() completes servicePrepare.
    h.player.service();
    for(uint8_t i = 0; i < 5; i++) {
        h.sink.consumeSample();
        h.player.service();
        assert(h.player.samplesPlayed() == h.sink.samplesWritten());
    }
    assert(h.player.samplesPlayed() == 6);
    assert(h.sink.samplesWritten() == 6);
}

void test_each_sample_played_corresponds_to_each_sample_written() {
    AudioPlayerTestHandles h;
    h.setStorageData(fake_adpcm_data, fake_adpcm_byte_count);
    h.player.start(0, BUF_SIZE*5, SAMPLE_RATE_HZ);
    h.player.service();
    for(auto i = 0; i < BUF_SIZE*5; i++) {
        h.player.service();
        h.sink.consumeSample();
        assert(h.sink.lastSampleWritten() == fake_decoded_pcm_data[i]);
    }
}

void test_successful_playback_enters_finished()
{
    AudioPlayerTestHandles h;
    h.player.start(0, 1, SAMPLE_RATE_HZ);
    h.player.service(); // first service() completes servicePrepare.
    h.player.service();
    h.sink.consumeSample();
    h.player.service();
    assert(h.sink.samplesWritten() == 1);
    assert(h.player.isFinished());
}

void test_refill_one_buffer_loads_raw_sector_bytes_into_sample_buffer()
{
    AudioPlayerTestHandles h;

    auto& storageData = h.storage.getStorageData();
    auto spoolerBuffer = h.player.debug_getSpooler().getRefillBuffer(0);

    h.player.start(0, CLIP_LENGTH_SAMPLES, SAMPLE_RATE_HZ);
    assert(h.player.isActive());
    h.player.service();

    auto* spoolerBytes =
        reinterpret_cast<const uint8_t*>(spoolerBuffer.data);

    for (size_t i = 0; i < 5; ++i) {
        assert(spoolerBytes[i] == storageData.data[0][i]);
    }
}

void test_buffers_do_not_repeat() {
    AudioPlayerTestHandles h;
    h.setStorageData(fake_adpcm_data, fake_adpcm_byte_count);
    h.player.start(0, BUF_SIZE * 5, SAMPLE_RATE_HZ);
    h.player.service();

    int16_t lastBufferData[BUF_SIZE];
    bool haveLastBuffer = false;

    for (auto i = 0; i < 5; i++) {
        for (auto j = 0; j < BUF_SIZE; j++) {
            h.player.service();
            h.sink.consumeSample();
        }

        RefillBuffer currentBuffer =
            h.player.debug_getSpooler().getRefillBuffer(i % 4);

        if (haveLastBuffer) {
            assert(memcmp(
                currentBuffer.data,
                lastBufferData,
                BUF_SIZE * sizeof(int16_t)
            ) != 0);
        }

        memcpy(
            lastBufferData,
            currentBuffer.data,
            BUF_SIZE * sizeof(int16_t)
        );

        haveLastBuffer = true;
    }
}


void test_buffers_stay_refilled_during_playback()
{
    AudioPlayerTestHandles h;
    h.player.start(0, CLIP_LENGTH_SAMPLES, SAMPLE_RATE_HZ);
    assert(h.player.isActive());
    while(h.player.isActive()) {

    }
}

void test_non_refilled_next_buffer_causes_underrun() {
    AudioPlayerTestHandles h;
    h.player.start(0, BUF_SIZE*5, SAMPLE_RATE_HZ);
    h.player.service();
    h.storage.setReady(false);
    for(auto i = 0; i < BUF_SIZE*4 + 1; i++) {
        h.player.service();
        h.sink.consumeSample();
    }
    h.player.service();

    assert(h.player.getState() == AudioPlayer::State::Underrun);
}

void test_sink_prepare_failure_causes_error() {
        AudioPlayerTestHandles h({.sinkFailPrepare=true});
    h.player.start(0, 1, SAMPLE_RATE_HZ);
    h.player.service();
    assert(h.player.getState() == AudioPlayer::State::Error);
}

void test_read_failure_causes_player_error() {
    AudioPlayerTestHandles h({.storageFailRead=true});
    h.player.start(0, 1, SAMPLE_RATE_HZ);
    h.player.service();
    assert(h.player.getState() == AudioPlayer::State::Error);
}

int main()
{
    test_initial_state_is_idle();
    test_start_enters_prepare_without_touching_sink();
    test_service_prepare_calls_sink_prepare();
    test_successful_prepare_enters_playback();
    test_start_while_playing_stops_current_playback_first();
    test_start_from_finished_enters_prepare_without_stopping();
    test_service_playback_consumes_samples();
    test_samples_played_equals_samples_written();
    test_each_sample_played_corresponds_to_each_sample_written();
    test_successful_playback_enters_finished();
    test_refill_one_buffer_loads_raw_sector_bytes_into_sample_buffer();
    test_buffers_do_not_repeat() ;
    test_non_refilled_next_buffer_causes_underrun();
    test_sink_prepare_failure_causes_error();
    test_read_failure_causes_player_error();
    std::cout << "Tests completed without errors.";
    return 0;
}
