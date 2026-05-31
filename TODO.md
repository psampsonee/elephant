# Restarting the project

[x] Write a TODO
[ ] Write a Readme - 3 hr
[ ] Look over all files - 1.5 hr
[ ] Compile the project in some form and run it on a dev board - 3 hr
[ ] Resistance Checks - 0.5 hr
[ ] Troubleshoot fabricated board and find out what went wrong - 5 hr
[ ] Verify electrical schematics in brief:
    [ ] Power Supply - 3 hr
    [ ] STM32 wiring - 3 hr
    [ ] I2S amplifier - 2 hr
    [ ] EEPROM - 1 hr
    [ ] D-Flip Flop - Timing diagram, states, all of it - 3 hr
[ ] Check status of all components - Own (refresh), buy again, replace - 2 hr

# SSM2518 Eval Board
## Setup / Schematic
[ ] Create KiCad circuit from original circuit - 1 hr
[ ] Check SSM2518 reference schematic / required passives / I2C address straps - 1 hr

## Firmware
[ ] Get I2S audio test to compile again - 2 hr
[ ] Test I2S code with logic analyzer - 2 hr
[ ] Confirm I2C config/write sequence for SSM2518 - 1 hr
[ ] Add simple known test tone output before real animal audio - 1 hr
[ ] Test I2S code with logic analyzer - 2 hr

## PCB
[ ] Layout audio test PCB - 5 hr
[ ] Verify PCB - 2 hr
[ ] Check audio routing: MCLK/BCLK/LRCLK/DATA short, clean, referenced to ground - 0.5 hr
[ ] Check amplifier output / speaker current / thermal assumptions - 0.5 hr

## Ordering
[ ] Create BOM, choosing up-to-date parts - 2 hr
[ ] Optional: create BOM for entire board while doing this - +1 hr
[ ] Order PCB - 0.5 hr
[ ] Order parts - 0.5 hr

## Bring-up
[ ] Resistance checks before power - 0.5 hr
[ ] Power board without speaker; verify rails and amp config - 1 hr
[ ] Verify I2S clocks on board - 1 hr
[ ] Play test tone through speaker - 1 hr
[ ] Play real elephant audio sample - 1 hr
[ ] Note fixes needed for main board - 1 hr

# Continuing the project

[ ] Verify power requirements with the breadboard prototype ( black pill sleep current ) - 3 hr
[ ] Migrate to 4-layer board design - 10 hr
    [ ] Layer 2 is JUST ground
    [ ] power ALWAYS drops to layer 3.
    [ ] I2S master clk bit clk and data lines all STAY on top layer.
    [ ] slow signals to bottom layer (4) away from audio signals
[ ] Verify board - 10 hr
    [ ] Ground loops
    [ ] Do not cross high-frequency lines
    [ ] Put buck conv. input caps right up against VIN pins
    [ ] Thermal via stitching - chip pads to GND
    [ ] Layer 2 ( from top ) is ground, Layer 3 ( from top ) is 3.3V and 9V
[ ] Fabricate a new board - 3 hr
[ ] Resistance Checks - 0.5 hr
[ ] Verify new board - 10 hr
[ ] Run tests and verify functionality of board - 6 hr
[ ] If requirements are met, put together the complete project
[ ] Tie documentation up into a neat bow - 3 hr
[ ] The end.

68.5 hr total - 137 hr commitment

I want to use a tilt switch to cause the enable pin of an LT8640 to turn on with the enable pin. Maybe it could drive the J of a JK flip flop through an RC filter. Then I want to use a GPIO from my microcontroller to turn the LT8640 using the K.