# Restarting the project

[x] Write a TODO
[x] Write a Readme - 3 hr
[x] Look over all files - 1.5 hr
[x] Compile the project in some form and run it on a dev board - 3 hr

# Audio playback

[x] Write audio player code - 20 hr

# SSM2518 Eval Board 
### (Note 1)

[ ] Create KiCad circuit - 3 hr
[ ] Check SSM2518 reference schematic / required passives / I2C address straps - 2 hr
[ ] Order PCB / parts - 2 hr
[ ] Resistance checks before power - 0.5 hr
[ ] Power board without speaker; verify rails and amp config - 1 hr
[ ] Verify I2S clocks on board - 1 hr
[ ] Play test tone through speaker - 1 hr
[ ] Play real elephant audio sample - 1 hr

# Target Firmware
### (Note 1)
[ ] Write I2S code - 6 hr
[ ] Write EEPROM code - 6 hr
[ ] Write main state machine code - 12 hr
[ ] implement playback cooldown using RTC - 6 hr
[ ] Determine sleep management functionality - 3 hr
[ ] Write sleep management code - 6 hr

# Tilt Switch Verification
[ ] Design tests for tilt switch circuit - 1 hr
[ ] Breadboard tilt switch circuit - 0.5 hr
[ ] Verify circuit meets specified requirements - 1 hr

# Power/Sleep Management Measurements
[ ] Measure SSM, EEPROM, and black pill currents across the target states and at desired volume - 3 hr
[ ] Re-evaluate power requirements based on measurements - 2 hr
[ ] Modify circuit schematics according to conclusions - 2 hr

# Final PCB
[ ] Layout final PCB - 15 hr
[ ] Verify PCB - 2 hr
[ ] Check audio routing: MCLK/BCLK/LRCLK/DATA short, clean, referenced to ground - 0.5 hr
[ ] Check amplifier output / speaker current / thermal assumptions - 0.5 hr

# Ordering
[ ] Create BOM, choosing up-to-date parts - 2 hr
[ ] Optional: create BOM for entire board while doing this - +1 hr
[ ] Order PCB - 0.5 hr
[ ] Order parts - 0.5 hr

# Bring-up
[ ] Resistance checks before power - 0.5 hr
[ ] Power board without speaker; verify rails and amp config - 1 hr
[ ] Verify I2S clocks on board - 1 hr
[ ] Play test tone through speaker - 1 hr
[ ] Play real elephant audio sample - 1 hr
[ ] Verify shutdown / wakeup path - 3 hr
[ ] Note fixes needed for main board - 1 hr

# Finishing up project
[ ] Run tests and verify functionality of board - 6 hr
[ ] Enclosure design - 3 hr
[ ] Final integration - 2 hr
[ ] Tie documentation up into a neat bow - 3 hr
[ ] The end.

# Notes
1. Target firmware and eval-board hardware work may proceed in parallel.
