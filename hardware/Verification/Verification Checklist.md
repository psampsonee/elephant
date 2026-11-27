# Rev A Verification Checklist

### 0. Initial Inspection
To be completed on a bare board before component installation.

Prime suspects for bridges:
- TP11 to VBackup

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
1. Immediately disconnect power from the board under test
2. Check whether the current limiting is momentary or sustained.
3. Check whether the buck output reaches 3.3 V.
4. If these things remain as expected, increase the current limit, not to exceed 1A as measured by the AD.

Expected results:

No fizzing or popping immediately upon plugging in.
No sudden current spikes after initial inrush; Measured current should remain below 0.5A.
Buck converter and surrounding components remain cool to the touch after one minute.

Measured results:

- [ ] Buck startup behavior - waveform sufficiently matches simulations with explainable qualifications

- [ ] Buck converter generates 3.3V on output node

Procedure

Probe TP27 and TP26 on the voltage setting while a 6V source is provided on the 6V node.

Expected Result:

Multimeter should read 3.3V.

Measured Result:

- [ ] No-load, disabled test: power consumption

Procedure:

Install a 10kOhm resistor on a breadboard. Feed one side of the resistor with the 6V supply and feed the 6V input of the buck converter from the other side. measure the voltage across the resistor with the DMM. Record the results.

Expected value:

<1uA, 3uA max

Measured value:

Measurements:

- [ ] No-load, enabled test: power consumption

Parallel a strip of wire and a 10kOhm resistor on a breadboard. Feed one side of the wire with the 6V supply and feed the 6V input of the buck converter from the other side.

Ensure stable 3.3V from the output of the buck converter by measuring the voltage from TP27 to TP26.

Remove the wire.

Repeat the voltage check from TP27 to TP26.

Measure the voltage across the resistor with the DMM. Record the results.

Expected value:

<1.7uA, 4uA max

Measured value:

- [ ] Small-load test

Procedure

Hand-solder 0-ohm bridge. Run the DMM on the mA current setting in series with the positive lead of the 6V power supply to the board.

Expected value: 
~10mA

Measured value:

### 2. Power-Or

#### Initial bring-up

The following tests should be performed after all parts for the ideal-diode power-or circuit are installed.

Convention: negative current is current into a source such as the coin cell.

With no coin cell inserted:
- [ ] Backup node is 3.3V during buck converter operation.
- [ ] Coin cell node is ~0V during buck converter operation.
- [ ] Secondary diode control node to GND ~<3.3V.

With coin cell inserted and buck converter off:
- [ ] Backup node is ~3V
- [ ] Buck converter node is ~0V
- [ ] Secondary diode control node to GND ~0V

#### Transitions
Observe on oscilloscope:

Use TP6 for Backup power node and the unpopulated low-side pad of R5 for the control node. 

- [ ] Backup power node - No peaks or dips outside of 2.0V and 3.6V:
    - [ ] Buck on, coin insertion
    - [ ] Buck on, coin removal
    - [ ] Coin in, buck turned on
    - [ ] Coin in, buck turned off
- [ ] Secondary diode control node (account for scope probe loading):
    - [ ] Coin in, buck turned on - ~0 to ~3.3V
    - [ ] Coin in, buck turned off - ~3.3V to ~0V

#### Reverse-current conditions - These might legitimately need a uA DMM:

- [ ] Buck on, coin cell in: <3uA from secondary Vin pin to coin cell. This may need a breadboard jig.
- [ ] Buck off, coin cell in: <1uA from secondary Vin pin to coin cell.

### 3. STM32

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

### 4. Tilt Switch Circuit

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

### 5. Audio

Before speakers are installed:
- [ ] Amplifier outputs - check that no signal is coming out besides maybe some high-frequency noise.
- [ ] I2C functionality - register reads, writes, configuration
- [ ] Idle power consumption when enabled - verification from datasheet

After speakers are installed:
- [ ] Audio quality
    - [ ] audible distortion, noise
    - [ ] Clipping (oscilloscope)
    - [ ] playback interruptions
    - [ ] quantify THD for 1 kHz test tone, LP filtering and osc. FFT
- [ ] Shutdown power consumption - subtracted from other idle peripherals, verification from datasheet
    - [ ] Hardware shutdown
    - [ ] Enabled but idle
    - [ ] Playing audio

### 6. EEPROM

- [ ] SPI functionality
- [ ] Successful writes
- [ ] Successful reads
- [ ] Writing energy consumption per write operation - average, 512 bytes
- [ ] Reading power consumption - average, at intended clock
    - [ ] Active read pattern
    - [ ] Effective read pattern during playback operation (silent audio sink) over several buffer refill cycles
- [ ] Idle power consuption - average for however long

### 7. Power Consumption Benchmarks
For whatever measurement method is used, the upper bound on current will be the uncertainty of the measurement method plus the measurement value.

- [ ] Total board current measurement from 6V supply, buck converter disabled - Less than 3uA
- [ ] Ideal diode Vin leakage current during buck shutdown, <1uA
- [ ] Ideal diode status node leakage during buck shutdown, ~1uA

- [ ] STM32 backup-only power consumption verification

The following should be comparibly negligable to simulation measurements:
- [ ] GPIO_buck_en pin leakage current - STM32 off
- [ ] ADC-sw_sese pin leakage current - STM32 off

### 8. System Integration

The following tests should be performed after all systems are independently installed and verified.

- [ ] buck converter wakeup verification - Wakeup circuit enables buck converter
- [ ] buck converter shutdown verification - STM32 reliably shuts down buck converter
- [ ] Repeated power-on, wakeup, hold and shutdown cycles reliably produce the same result
- [ ] repeated wakeup behavior - repeated activation of wakeup RC network reliably wakes up buck converter
- [ ] STM32 wakeup verification - buck converter remains on long enough for GPIO_buck_en to assert
- [ ] GPIO_buck_en functional verification - STM32 can keep buck converter on by pulling GPIO_buck_en high

- [ ] Total current from coin cell to board, buck converter off
- [ ] A threshold voltage can be established which rejects unintended wakeups on ADC_sw_sense.

Final Checks:
- [ ] Valid shake initiates complete elephant sound playback.
- [ ] Subsequent shakes within the lockout period do not initiate playback.
- [ ] Playback is permitted after the RTC lockout period expires.
- [ ] System returns to deep sleep following playback or a rejected wakeup.
- [ ] Total energy consumption per successful playback cycle.
- [ ] Total energy consumption per rejected wakeup cycle.
- [ ] Battery life projection using measured system parameters.
