# Hardware Checks for Evaluation Board
## Schematic Checks
### 1. Power
- [x] Values of LT8640 passives match simulated LTSpice values.
- [x] Power OR network topology verified against reference schematic
- [x] Power OR network values verified via simulation or calculations
- [x] Power OR back-current impedance to coin cell deemed acceptable
- [x] Power OR decoupling caps are acceptable values
- [x] Test points identified and verified
- [x] 0-ohm bridges identified and verified
- [x] Inductor saturation - provide documented calculations verifying value.
- [x] Capacitor voltage and DC bias deratings keep capacitance values within specification
- [x] Resistors are rated for anticipated peak and steady state currents based on LTSpice
- [x] Regulator is capable of supplying expected steady state current without going into shutdown.
- [x] Power network simulated against several conditions:
    - [x] Startup
    - [x] Steady State
    - [x] Source-transition
    - [x] Shutdown
- [x] peak current and RMS current extracted from simulation and checked against component ratings as relevent
- [x] Worst-case node voltages checked against component absolute-maximum ratings
- [x] Thermal checks for devices
    Gather steady state (playback) and peak power + duration, and/or integrated energy
    - [x] LT8640
    - [x] LM66100 (x2)
    - [x] Resistors
    compare against whatever thermal limits/guidance the datasheet actually provides
    flag anything that needs layout-dependent thermal verification
    require ~20% margin where a meaningful numeric limit exists

### 2. Tilt Switch Circuit
- [x] Topology verified against test circuit
- [x] Values verified against test circuit
- [x] Test points identified and verified
- [x] 0-ohm bridges identified and verified

### 3. MCU
- [x] Topology verified against datasheet and/or known-good circuit
- [x] VCAP1 value verified from datasheet
- [x] LSE crystal impedance, capacitance, frequency verified against calcs from datasheet
- [x] LSE network capacitor values verified against calcs from datasheet
- [x] LSE crystal startup/load-cap tolerances
    - Verify on hardware (see below)
- [x] HSE crystal frequency is an acceptable value for audio playback
- [x] HSE crystal impedance, capacitance verified against calcs from datasheet
- [x] HSE network capacitor values verified against calcs from datasheet
- [x] HSE crystal startup/load-cap tolerances
    - TODO: Verify on hardware:
        - Measure oscillator trace stray capacitance and verify against 3pF assumption
        - Verify oscillator drive level is below the selected 200uW limit for selected crystal using AN2867 3.5.2.
- [x] Has proximal AND distal decoupling caps at acceptable values
- [x] Test points identified and verified
- [x] 0-ohm bridges identified and verified
- [x] NRST circuit
- [x] Check NRST minimum pulse / pull-up / capacitor against datasheet recommendations
    - This configuration matches the datasheet recommendation found on pg 95 of the datasheet.
    - **Layout requirement**: ensure that C_NRST is placed as close to the STM32 as possible.
- [x] BOOT pin state - defaults to allowing normal boot, but resettable.
- [x] SWD pins
- [x] VDDA/VSSA (analog circuit) - capacitors and reliability
- [x] All VDD/VSS pins have connections
- [x] VDD/VSS capacitors are placed
- [x] Pin assignments (and functions) match a possible configuration in CubeMX
    - verify 3.072 MHz BCLK and approximately 48 kHz LRCLK on hardware (audio bringup)
- [x] Pin assignments are not absurd for board layout
    - This will be a layout check.
    - [ ] Keep pins going to the same place close together
    - [ ] Decide beforehand where neighbors will be in relation to MCU and sanity-check pin locations for interconnections
- [x] Verify power sequencing differences from Black Pill reference design
- [x] Verify a recovery method exists if firmware disables/reconfigures SWD (i.e. reset or BOOT)
- [x] Check that any peripherals will be successfully driven given I/O current limits.

### 4. EEPROM
- [x] Pin functions backchecked against datasheet
- [x] Pin connections backchecked against datasheet
    - !S needs a pullup resistor - added
- [x] Has proximal AND distal decoupling caps at acceptable values
- [x] Test points identified and verified
- [x] 0-ohm bridges identified and verified
    - N/A
- [x] **Default** states of pins do not:
    - [ ] Erase or change data
    - [ ] Put the EEPROM in an undefined state
    - [ ] Damage the EEPROM
    - [ ] Make the EEPROM consume unnecessary power
    - This is a final board eval check.
- [x] Chosen EEPROM works with 3.3V SPI signals
- [x] Maximum clock speed of the EEPROM exceeds intended STM32 SPI clock speed
    - Up to 50 MHz; concievably up to 300KB/s > 48KB/s for 96kHz sample rate at mono 4-bit/s ADPCM
- [x] Check write-protect behavior during brownout/power collapse during writes when attached to debugger.
    - This is a hardware check.
- [x] Confirm SPI timing including CS setup/hold, not merely max SCK.
    - This is a firmware check.

### 5. Audio Out
- [x] Topology verified against datasheet and/or known-good circuit
- [x] Pin functions backchecked against datasheet
- [x] Pin connections backchecked against datasheet
- [x] Checked capacitor values against available engineering calculations
    - N/A - Decoupling caps according to datasheet recommendations.
- [x] Has proximal AND distal decoupling caps at acceptable values
- [x] Test points identified and verified
- [x] 0-ohm bridges identified and verified
- [x] Config pin reset states
- [x] Address pin reset states
- [x] shutdown pin reset states
- [x] I2S logic levels 0V and 3.3V
- [x] allowed MCLK/BCLK/LRCLK relationships versus what STM32 can actually generate
- [x] speaker impedance/power against amplifier operating conditions
- [x] Output capacitor / filter requirements per datasheet
- [x] Output network matches datasheet recommendation for short speaker leads
- [x] Check anticipated junction temperature against maximum ratings in datasheet.
- [x] Verify I2S word length / frame format can be supplied by STM32
    - 16bits/channel/frame is an option, MSB first
- [x] Check amplifier input and control pin states when MCU reset/unpowered conditions that can actually occur.

### 6. Debug Interface
- [x] UART lines are all present
- [x] UART lines have correct topology
- [x] SWD lines are all present
- [x] SWD lines have correct topology

### 7. Interface Checks
- [x] Every IC supply pin checked for:
    - [x] correct voltage
    - [x] acceptable voltage range
    - [ ] adequate capacitor voltage rating
        - Must complete component selection.
- [x] Absolute-max / signal-level compatibility checked between devices
- [x] Power-up/default states of important control pins verified
- [x] MCU boot/reset configuration verified
- [x] No required pull-ups/pull-downs omitted
- [x] Connector pinouts independently backchecked
- [x] Grounds and power-net names checked for accidental separation/connection
- [x] ERC run and every warning reviewed rather than blindly waived
- [x] Every external interface has a usable ground reference available for probing
- [x] Programming/debug connector physically includes everything needed to recover a blank board
- [x] Confirm no signal depends upon firmware driving it correctly during MCU reset
- [x] Confirm unused pins are intentionally handled
- [ ] Confirm footprint/package selections against ordering part numbers
- [x] Every connector is checked for mis-plug or reversed-plug consequences
- [x] Every test point can be physically probed after assembly 
    (include this in board layout as well; tall components may make this hard)
- [ ] Verify PCB footprints:
    - [ ] Dimensions
    - [ ] Pin 1 orientation
    - [ ] Exposed pads
    - [ ] Courtyard
- [ ] Dead-MCU debug audit: identify every node that would need to be measured or controlled to diagnose a board where the MCU never runs; provide test access as appropriate.

## Board Layout Checks
