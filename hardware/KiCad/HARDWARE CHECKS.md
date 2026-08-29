# Hardware Checks for Evaluation Board
## Schematic Checks
### 1. Power
- [ ] Values of LT-8640 passives match simulated LTSpice values.
- [ ] Power OR network topology verified against reference schematic
- [ ] Power OR network values verified via simulation or calculations
- [ ] Power OR back-current impedance to coin cell deemed acceptable
- [ ] Power OR decoupling caps are acceptable values
- [ ] Test points identified and verified
- [ ] 0-ohm bridges identified and verified
- [ ] Inductor saturation - provide documented calculations verifying value.
- [ ] Capacitor voltage and DC bias deratings keep capacitance values within specification
- [ ] Resistors are rated for anticipated peak and stready state currents based on LTSpice
- [ ] Regulator is capable of supplying expected steady state current without going into shutdown.

### 2. Tilt Switch Circuit
- [ ] Topology verified against test circuit
- [ ] Values verified against test circuit
- [ ] Test points identified and verified
- [ ] 0-ohm bridges identified and verified

### 3. MCU
- [ ] Topology verified against datasheet and/or known-good circuit
- [ ] VCAP1 value verified from datasheet
- [ ] LSE crystal impedance, capacitance, frequency verified against calcs from datasheet
- [ ] LSE network capacitor values verified against calcs from datasheet
- [ ] LSE crystal startup/load-cap tolerances
- [ ] HSE crystal frequency is an acceptable value for audio playback
- [ ] HSE crystal impedance, capacitance verified against calcs from datasheet
- [ ] HSE network capacitor values verified against calcs from datasheet
- [ ] HSE crystal startup/load-cap tolerances
- [ ] Has proximal AND distal decoupling caps at acceptable values
- [ ] Test points identified and verified
- [ ] 0-ohm bridges identified and verified
- [ ] NRST circuit
- [ ] BOOT pin state - defaults to allowing normal boot, but resettable.
- [ ] SWD pins
- [ ] VDDA/VSSA (analog circuit) - capacitors and reliability
- [ ] All VDD/VSS pins have connections
- [ ] Pin assignments (and functions) match a possible configuration in CubeMX
- [ ] Pin assignments are not absurd for board layout
    - [ ] Keep pins going to the same place close together
    - [ ] Decide beforehand where neighbors will be in relation to MCU and sanity-check pin locations for interconnections

### 4. EEPROM
- [ ] Pin functions backchecked against datasheet
- [ ] Pin connections backchecked against datasheet
- [ ] Has proximal AND distal decoupling caps at acceptable values
- [ ] Test points identified and verified
- [ ] 0-ohm bridges identified and verified
- [ ] **Default** states of pins do not:
    - [ ] Erase or change data
    - [ ] Put the EEPROM in an undefined state
    - [ ] Damage the EEPROM
    - [ ] Make the EEPROM consume unnecessary power
- [ ] Chosen EEPROM works with 3.3V SPI signals
- [ ] Maximum clock speed of the EEPROM exceeds intended STM32 SPI clock speed

### 5. Audio Out
- [ ] Topology verified against datasheet and/or known-good circuit
- [ ] Pin functions backchecked against datasheet
- [ ] Pin connections backchecked against datasheet
- [ ] Checked capacitor values against available engineering calculations
- [ ] Has proximal AND distal decoupling caps at acceptable values
- [ ] Test points identified and verified
- [ ] 0-ohm bridges identified and verified
- [ ] Config pin reset states
- [ ] Address pin reset states
- [ ] Control pin reset states
- [ ] I2S logic levels 0V and 3.3V
- [ ] allowed MCLK/BCLK/LRCLK relationships versus what STM32 can actually generate
- [ ] speaker impedance/power against amplifier operating conditions
- [ ] output topology requires no accidental ground-referenced probing
- [ ] Output capacitor / filter requirements per datasheet

### 6. Debug Interface
- [ ] UART lines are all present
- [ ] UART lines have correct topology
- [ ] JTAG lines are all present
- [ ] JTAG lines have correct topology

### 7. Interface Checks
- [ ] Every IC supply pin checked for:
    - [ ] correct voltage
    - [ ] acceptable voltage range
    - [ ] adequate capacitor voltage rating
- [ ] Absolute-max / signal-level compatibility checked between devices
- [ ] Power-up/default states of important control pins verified
- [ ] MCU boot/reset configuration verified
- [ ] No required pull-ups/pull-downs omitted
- [ ] Connector pinouts independently backchecked
- [ ] Grounds and power-net names checked for accidental separation/connection
- [ ] ERC run and every warning reviewed rather than blindly waived
- [ ] Every external interface has a usable ground reference available for probing
- [ ] Programming/debug connector physically includes everything needed to recover a blank board
- [ ] Confirm no signal depends upon firmware driving it correctly during MCU reset
- [ ] Confirm unused pins are intentionally handled
- [ ] Confirm footprint/package selections against ordering part numbers
