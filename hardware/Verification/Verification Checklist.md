# Rev A Verification Checklist

### 0. Initial Inspection
To be completed on a bare board before component installation.

Visual Inspection
- [ ] Board dimensions match specifications
- [ ] Solder mask fits around traces
- [ ] Silk screen fits around solder mask

Solder Bridges
- [ ] Solder mask has no visibly crossing nodes when compared to 3D model

Continuity - Use KiCad highlighting as a visual aid to identify exposed copper on nodes.
Check these are continous on the physical board as seen on KiCad:
- [ ] 6V node
- [ ] Pre-bridge buck output node
- [ ] Post-bridge buck output node
- [ ] Ground node on all ground pads/through-holes
- [ ] VBackup

Shorts
Check these nodes are NOT continuous:
- [ ] 6V to Ground
- [ ] 6V to pre-bridge buck output
- [ ] 6V to post-bridge buck output
- [ ] Pre-bridge buck output to Ground
- [ ] Post-bridge buck output to Ground
- [ ] Pre-bridge buck output to post-bridge buck output
- [ ] VBackup to Ground
- [ ] 6V to VBackup
- [ ] Post-bridge buck output to VBackup
- [ ] Pre-bridge buck output to VBackup

### 1. Buck Converter

Tests

The following test should be done after all buck converter components (including the LED and its resistor) are installed, but before the 0V output bridge is installed on the board.

- [ ] Smoke test

Procedure

Set Analog Discovery current limit to 0.5A if possible.

Apply 5V to the input node of the buck converter for 1 minute using the Analog Discovery power supply function. Observe input current with DMM on current setting in series with the input terminals.

If inrush current triggers the current-limiting function:
1. Check whether the current limiting is momentary or sustained.
2. Check whether the buck output reaches 3.3 V.
3. If these things remain as expected, increase the current limit, not to exceed 1A as measured by the AD.

Expected results:

No fizzing or popping immediately upon plugging in.
No sudden current spikes after initial inrush; Measured current should remain below 0.5A.
Buck converter and surrounding components remain cool to the touch after one minute.

Measured results:

- [ ] Buck startup behavior - waveform sufficiently matches simulations with explainable qualifications

- [ ] Buck converter generates 3.3V on output node

Procedure

Probe TP23 and TP26 on the voltage setting while a 6V source is provided on the 6V node.

Expected Result:

Multimeter should read 3.3V.

Measured Result:

- [ ] No-load, disabled test: power consumption

Procedure:

Measurements:

- [ ] No-load, enabled test: power consumption

TODO

- [ ] Small-load test

TODO

Procedure

Hand-solder 0-ohm bridge. Repeat current test with new load (LED).

### 2. STM32

Tests

The following test should be preformed after the STM32 and its essential components (including pushbuttons) are installed and before any peripheral ICs and their passives are installed.

- [ ] Main power supply stability
- [ ] Backup power supply stability
- [ ] Analog power supply stability
- [ ] SWD functionality
- [ ] UART/firmware functionality - UART command-response
- [ ] LSE Clock functionality
- [ ] HSE Clock functionality
- [ ] Confirm HSE usage by firmware
- [ ] Confirm LSE usage by RTC
- [ ] NRST functionality
- [ ] BOOT0 functionality
- [ ] idle power consumption verification
- [ ] RTC functionality on backup power - reports accurate time change between power cycles on main supply
- [ ] backup-only power consumption verification

### 3. Tilt Switch Circuit

Tests

The following tests should be performed after the STM32 is verified and before all other peripherals are installed.

RC / Diode network verification:
- [ ] RC time constant verification - equal to design
- [ ] buck_en signal verification - similar to sim
- [ ] Idle power consumption verification (GPIOs floating) - similar to sim
- [ ] GPIO_buck_en functionality - STM32 can drive buck_en node
    - [ ] A. Can reliably hold the node above 1.05V
    - [ ] B. Can reliably hold the node below 0.95V
- [ ] ADC_sw_sense functionality - STM32 can adequately sense ADC_sw_sense node

Switch verification: The chosen switch orientation...
- [ ] reliably produces a wakeup condition
- [ ] Is open when the board is set "upright"
- [ ] Minimizes* unintended wakeups with ordinary movement

*: Provided that some wakeups can be rejected in firmware with the ADC_sw_sense pin.

### 4. Power-Or
### 5. Audio
### 6. EEPROM
### 7. Power Consumption Benchmarks

- [ ] Total board current measurement from 6V supply, buck converter disabled - Less than 3uA

The following should be comparibly negligable to simulation measurements:
- [ ] GPIO_buck_en pin leakage current - STM32 off
- [ ] 
- [ ] ADC-sw_sese pin leakage current - STM32 off

### 8. System Integration

The following tests should be performed after all systems are independently installed and verified.

- [ ] buck converter wakeup verification - Wakeup circuit enables buck converter
- [ ] buck converter shutdown verification - STM32 reliably shuts down buck converter
- [ ] Repeated power-on, wakeup, hold and shutdown cycles reliably produce the same result
- [ ] repeated wakeup behavior - repeated activation of wakeup RC network reliably wakes up buck converter
- [ ] STM32 wakeup verification - buck converter remains on long enough for GPIO_buck_en to assert
- [ ] GPIO_buck_en functional verification - STM32 can keep buck converter on by pulling GPIO_buck_en high


- [ ] A threshold voltage can be established which rejects unintended wakeups on ADC_sw_sense.
