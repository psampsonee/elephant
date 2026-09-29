# SSM2518 Audio Evaluation Board

Goal: make a small test PCB that proves the Elephant audio chain:
STM32/Black Pill → I2S + I2C → SSM2518 → speaker.

[ ] Add I2S header: MCLK, BCLK, LRCLK, SDATA, GND
[ ] Add I2C header: SCL, SDA, GND, 3V3
[ ] Add logic analyzer test points for all I2S lines
[ ] Add test points for 3V3, GND, amp enable/config pins
[ ] Add speaker screw terminal or JST connector
[ ] Add jumpers/solder bridges for address/config options
[ ] Add optional shutdown/enable control pin header
[ ] Include M95M04 EEPROM on audio test PCB - 1 hr
[ ] Add SPI test points/header for EEPROM: CS, SCK, MISO, MOSI, GND - 0.5 hr
[ ] Write/restore EEPROM loading script or firmware path - 2 hr
[ ] Verify EEPROM read speed is enough for audio streaming - 2 hr
[ ] Test EEPROM read while I2S playback is active - 3 hr
[ ] Confirm buffering strategy: samples vs bytes, packet size, underrun behavior - 2 hr
[ ] Play real elephant audio from EEPROM through SSM2518 - 2 hr