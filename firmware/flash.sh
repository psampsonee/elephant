#!/bin/bash

openocd -f interface/stlink.cfg -f target/stm32f4x.cfg -c "program build/elephant.elf verify reset exit"
