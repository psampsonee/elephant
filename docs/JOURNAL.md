### Parking Lot
- 4-layer board for noise and component placement
- Give the board to someone for review
- Backing up data between shutdowns using backup domain
- Code is a mess
- Test the buck converter circuit with components i already have to see if it would basically work in the real world as-designed (check if I changed it substantially since I got boards)
- Replace flip flop with momentary buck enable circuit to allow the MCU to self-latch the buck enable pin.
    OPEN QUESTION
    How long must the buck enable pulse be to guarantee MCU self-latch?
    OPEN QUESTION
    Can a passive RC + diode OR buck-enable circuit reliably hold EN long enough for MCU self-latch without unacceptable standby current? Prefer passive RC solution unless testing/simulation shows unreliable wake capture. Reject active assist circuitry unless its standby current is acceptably low.
    OPEN QUESTION
    How long does the abnormal switch condition last and is it enough to charge the capacitor?
    TEST PLAN
    Capture real tilt-switch waveform (including bounce and event duration), apply it to the candidate RC + diode EN circuit at worst-case coin-cell voltage, and measure EN peak voltage plus time above 1 V to determine whether passive wake capture is reliable.

### Log
2/1/2026 - Put together a TODO. Looking over files and README is next.
2/3/2026 
    - Started README.md.
    - Looked at all major components
    - Concerns about D-flip flop - Why did I choose to do this and what does it do in the circuit exactly?
    - Considered battery calculations
    - Considered state machine
    - Considered buck converter design choices
2/7/2026
    - Revised tilt switch / flip flop function: tilt switch turns buck on, MCU turns buck off.
    - Revised KICAD schematic to reflect above changes
    - Created a power condition table
    - Determined that BAT54 is good enough
        - 2uA backcurrent will not catastrophically fail CR2032
        - use of buck converter for power will not exceed 4 hours at a time, usually followed by a day or more of being on coin cell power
        - Therefore, the effect on the coin cell is acceptable.
2/10/2026
    - Resolved to use LM66100 instead of BAT54 for power switching
    - Added decoupling caps to flip flop
2/14/2026
    - Buck converter simulations done
    - Started working on LM66100 simulations
    - Modified schematic to use LM66100
2/15-3/1/2026 or so
    - Completed LM66100 model that works and mostly approximates electrical properties
3/7/2026
STATE:Simulation
    - Re-simulated buck converter in LTSpice with 4x L92 AAA batteries instead. Tested 3 different voltages and 4 different internal resistances. The batteries will not affect performance during the reasonable life of the batteries.
    - Began modelling power source OR circuit in LTSpice
        Goal: verify no harmful back-current into coin cell
    - Began modelling buck enable trigger circuit in LTSpice
        Goal: verify behaviour
CURRENT TARGET
Validate power source OR circuit behavior before modifying buck enable architecture

NEXT STEPS
1. Test OR circuit: 3 different voltages for each source
2. Measure backup voltage
3. Measure back-current to coin cell

THEN
- Finish buck enable trigger circuit
- Put D-flip flop in its own subckt (or replace)
- Test buck enable trigger circuit with emulated logic pin

