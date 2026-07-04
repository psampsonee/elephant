#!/bin/bash

openocd -f interface/stlink.cfg -f target/stm32f4x.cfg -c "program build/audio-test.elf verify reset exit"
