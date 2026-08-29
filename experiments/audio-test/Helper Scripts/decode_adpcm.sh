#! /bin/bash
{
    ffmpeg -hide_banner -loglevel error \
        -f lavfi -i 'anullsrc=r=48000:cl=mono' \
        -t 0 \
        -fflags +bitexact \
        -c:a adpcm_ima_wav -f wav pipe:1 |
        head -c 48

    cat fake_pcm_data.adpcm
} |
ffmpeg -hide_banner -loglevel error \
    -f wav -i pipe:0 \
    -f s16le -acodec pcm_s16le \
    fake_decoded_pcm_data.pcm
