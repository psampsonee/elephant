# Restarting the project

[x] Write a TODO
[ ] Write a Readme - 2 hr
[ ] Look over all files - 1.5 hr
[ ] Compile the project in some form and run it on a dev board - 3 hr
[ ] Resistance Checks - 0.5 hr
[ ] Troubleshoot fabricated board and find out what went wrong - 5 hr
[ ] Verify electrical schematics in brief:
    [ ] Power Supply - 3 hr
    [ ] STM32 wiring - 3 hr
    [ ] I2S amplifier - 2 hr
    [ ] EEPROM - 1 hr
[ ] Check status of all components - Own (refresh), buy again, replace - 2 hr

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
