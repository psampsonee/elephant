Milestones

Initial Prototype
- Play sound
- Read/write EEPROM
- Play sound while using EEPROM
- RTC alarms are implemented
- State machine works properly
- Sleep/Shutdown implemented and the prototype works functionally
- Prototype performs full cycle:
    sleep → wake → play → sleep
- startup and pin assertion time recorded (See next section)

Power (SPICE)
- Buck converter implemented, known working (as designed on schematic)
- Power OR working
- tilt switch/EN trigger working (~100ms enabled after tilt event, verified during prototyping)

Firmware (It largely exists, but big chunks dont or need to be rewritten)
Firmware architecture reviewed
Critical modules reviewed (state machine, audio, EEPROM)
Wake source correctly identified after reset
Unit tests implemented
Unit tests passing

Board readiness
Schematic reviewed
Power paths verified
Buck converter layout reviewed
Decoupling verified
Test points/0-ohm ties identified and added
Instrumentation points added (current measurement):
    shunt resistor or test pads for current
    buck enable signal probe
    VBAT probe
ERC/DRC

Bring-up
Board powers up, no overheating
3.3V rail stable
MCU programmable
Amplifier powers up, works
Audio playback verified

Verification
(board approaches simulation results for power consumption)
Low-power current measured
Buck-off current measured
Playing current measured and adjusted to balance audibility and battery life
Wake latency measured

Reliability
Several shake events tested
Sleep/wake cycles tested
failure modes tested: one battery or the other removed, tilt switch stuck, one thing or another won't turn on or off
Go to university and see if i can get time on a thermal camera, verify nothing heats more than necessary
Long-duration idle test (24–72 hours)

Most likely to stall: 
Playing a sound
Wake / power-gating logic
Board power-up