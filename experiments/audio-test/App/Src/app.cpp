#include "app.h"
#include "pwm_audio_sink.h"
#include "sd_card.h"
#include "audio_player.h"

extern PwmAudioSink sink;
extern SdCard storage;
extern AudioPlayer player;

extern "C" void app_main()
{
    uint8_t progstate = 0;
    player.start(CLIP_START_SECTOR, CLIP_LENGTH_SAMPLES, SAMPLE_RATE_HZ);
    while(player.getState() == AudioPlayer::State::Prepare ||
        player.getState() == AudioPlayer::State::Playback) {

        player.service();

        if (player.hasUnderrun()) {
            progstate = 2;
            (void) progstate;
            while(true) {}
        }

        if (player.getState() == AudioPlayer::State::Error) {
            progstate = 1;
            (void) progstate;
            while(true) {}
        }
    }
    player.stop();
}
