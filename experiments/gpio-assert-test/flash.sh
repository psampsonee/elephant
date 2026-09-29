#!/bin/bash

openocd -f interface/stlink.cfg -f target/stm32f4x.cfg -c "program build/gpio-assert-test.elf verify reset exit"
