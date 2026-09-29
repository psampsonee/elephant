#!/bin/bash
arm-none-eabi-gdb -q build/gpio-assert-test.elf \
  -ex "target extended-remote localhost:3333" \
  -ex "monitor reset halt" \
  -ex "load" \
  -ex "monitor reset halt" \
  -ex "disconnect" \
  -ex "quit"
