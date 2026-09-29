## 8/29/2026

Current State:

- Wrote schematic checklist for Rev A board

Next steps:

- Clean up LT-8640 LTSpice model and begin verifying component ratings in the power section, adjusting idealized assumptions.
- Establish one canonical cleaned-up LT-8640 baseline before beginning simulations. Record the source of each value (i.e. datasheet) for future reference.
    - Voltage-derated input/output capacitor values
    - Capacitor ESR, esp. on output cap.
    - Inductor DCR
    - Realistic battery voltage and source resistances
    - One parameterized load (parameterized current source)
- Each question gets a separate simulation file.
    - Startup at worst-case load (verify ~3.3V)
    - Load transient from idle to playback
    - Battery corner: Vbat_min and worst-case source resistances
    - Component stress: Peak/RMS currents and voltages
    - Shutdown: Check behavior when EN drops below 1 V
    - Source / OR behavior: Backfeed/source transitions (multiple tests)
        - Backfeed steady state
        - Transition transients
        
## 9/1/2026

Current State:

- Cleaned up LTSpice directory structure
- Began parameterizing LTSpice buck convertor model

Next Steps:

- Construct effective/test values from nominal values × derating/tolerance factors
- Apply those parameters throughout the LTspice model
- Populate nominal values, tolerances, derating factors, ESR/DCR, etc. from datasheets/design documentation; cite sources in bib.md

9/5/2026

Current State:

- Set up Buck Convertor LTSpice workspace and documentation files.
- Began gathering parameters and SPICE models from datasheets

Next Steps:

- Finish gathering parameters from datasheets, putting documentation in .inc/bib.md/bib.ods as needed
- Prepare test conditions.

9/6/2026

Current State:

- Gathered component parameters and models from vendors with documentation
- Ran initial bringup simulation

Next Steps:

- Sweep Distal Vin/Vout capacitors for anticipated current dips
- Test battery corners
- Test various loads
- Test startup under load
- Test shutdown

9/7/2026

Current State:

- Completed baseline simulation
- Produced C_IN_DISTAL sizing simulation during steady state
- For steady state, a capacitance of 47uF captures most of the improvement in VIN ripple and VIN minimum, with diminishing returns above that.

Next Steps:

- C_IN_DISTAL startup simulation and tests
- Battery corner tests.

9/12/2026

Current State

Re-defined test conditions - input bulk capacitor
Determined component measurements
Ran all three conditions and revised the above two based on results

Next Steps

Revise steady state power for 30% rather than 20% max playback power
Write load switching measurements in LTSpice

9/13/2026

All VIN-cap tests rerun with consistent battery states and recovery metrics. Next: tabulate results only—do not change tests unless the table exposes a problem.

9/19/2026

Current State

Verified VIN bulk capacitor and VOUT bulk capacitor selection.

Next Steps

Buck converter design verification checkoffs from existing checklist
Power-or circuit simulation:
    - Design criteria
    - Test questions
    - Corners / state transitions
    
9/20/2026

Current State

Checked Buck KiCad against LTSpice: topology and nominal values.
Added evaluation features to KiCad schematic.
Organized LTSpice folders.

Next Steps

Verify buck enable behavior.
    - Disable threshold, falling EN
    - Enable thresh, rising EN
    - Shutdown decay (Time from 3.3V to 1.8V) when EN pulled low quickly. Should be around (60uC per amp)s.
Investigate passive wake circuit with MCU self-hold.
    - determine required EN hold time from the results above
    - measure/estimate MCU boot-to-GPIO-assert time
    - see whether RC + diode can guarantee that at worst-case VBackup
    - check standby leakage
Power-or verifications

9/21/2026

Results:
- Time to decay when disabled: 863us.
- Time to reach minimum boot voltage (1.8V): 3.07ms

Next steps

Investigate passive wake circuit with MCU self-hold and nominal EN voltage thresholds.

9/22/2026

Current State
- Captured time from 1.73V (experimentally verified minimum GPIO voltage) applied to input rail to GPIO assert on STM32F401 in gpio-assert-test.
- Result:5.69ms
- Negligible observed run-to-run variation over several trials.
- Target time for RC filter to remain above 0.96V (LT8640 EN threshold): (5.69ms+0.00307ms)*1.2=~6.84ms (20% safety factor)

Next steps:
- Determine RC time constant to meet the requirement of decaying from 2.67V to 0.96V in 6.84ms
- Determine minimum viable tilt switch closed time (Let's say the RC must charge to at least 90% of 2.97V (which is 90% of 3.3V))
- Simulate using the selected impulse and RC values (as well as parasitics/nonideals) to verify.

9/26/2026

Current State
- Plans for impulse sensing via NMOS inverter
- Wrote up RC basis
- Simulated to verify answers to tilt switch circuit questions
    - EN hold time: 9.19 ms minimum vs. 6.84 ms required
    - RC charging effectively instantaneous relative to 100 µs assumed switch pulse
    - No meaningful GPIO backfeed/leakage observed

Next steps
- Pick parts
- Power OR ckt

9/27/2026

Current State
- Copied tilt switch wake circuit into KiCad
- Determined that a series resistor to the RC node of the wake circuit would suffice for switch sensing.
- Designed questions and tests for power-or circuit

Next Steps
- Perform Power-Or tests
- Complete power checklist
- Move on to MCU checks
- there was a magnitude error in the RC calculation. Fix it.

9/29/2026

Current State
- Recalculated RC values, updated docs.
- Re-simulated tilt switch circuit with datasheet component values, found that chosen parts exceed the new requirements.
- Produced baseline power-or simulation with old LM66100 model

Next steps
- Create and execute power handoff tests
- Create and execute source crossover test
- Create and execute reverse leakage tests (buck off/buck on)
- Create and execute Cbackup sweep test (variant of buck->coin cell test)
- Create and execute the four fault conditions highlighted (backup node short/diodes shorted/coin cell flipped/no coin cell)
- Complete power checklist
