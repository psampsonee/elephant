#include "pwm_audio_sink.h"
#include "sd_card.h"
#include "audio_player.h"
#include "tim.h"
#include "spi.h"

PwmAudioSink sink{htim4, htim3};
SdCard storage(hspi1, GPIOA, GPIO_PIN_4);
AudioPlayer player(storage, sink);
