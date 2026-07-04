#include "app.h"
#include "audio_player.h"

extern "C" void app_main(AppHandles* handles)
{
    //AudioPlayer::run(handles);
}


void play() {
    player_.start(16000);

fill all player buffers from SD;

player_.beginPlayback();

while (1) {
    refill buffers as needed;
}
}
