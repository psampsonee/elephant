# Buck Converter LTSpice Simulation Findings
## 1. VIN bulk smoothing capacitor
### Design Criteria
1. Exceed the minimum buck converter input voltage of 3.4VDC at worst-case battery voltage to maintain 3.3 V regulation at worst-case load.
    - 3.4V is needed to achieve 3.3V VOUT minimum according to VIN step testing using baseline model.
2. Output voltage ripple shall remain at or below 5% peak-to-peak of the nominal 3.3 V DC rail (0.165 VPP). Ripple shall be evaluated separately and verified not to compromise downstream device operation.
3. RMS/ripple current and peak voltage must remain within selected capacitor's ratings.
    - Each test will have two cases:
        High V_{OC}, Moderate R_{INT} - Corresponding to a new battery, and exposing 
        Moderate V_{OC}, High R_{INT} - Corresponding to a used battery with minimum internal resistance
        Low V_{OC}, High R_{INT} - Corresponding to and old battery
4. Input-capacitor charging shall not produce excessive battery voltage sag or sustained high-current loading during any transition (startup and playback in this case).
5. The volumetrically smallest capacitor that meets these requirements is desirable.

### Tests

Three tests will be run to answer the above questions and to determine a part to use for the input bulk capacitor. The tests and their purposes are as follows:

1. Startup
    - Determines worst-case initial currents and voltages, which informs:
        - Input Bulk capacitor current stress
        - Battery stress
        - Regulator startup time
        - Switching inductor current stress
    - Measurements:
        - Peak inrush current at battery and input bulk capacitor.
            A/B. new battery
            C/D. moderately used battery
        - Peak switching inductor current
            E. new battery
            F. moderately used battery
        - G. time for VIN to reach 3.4 V (buck regulation threshold), old battery
2. Steady-State
    - Determines input/output voltage regulation and ripple during steady-state playback, which affects:
        - Microcontroller / amplifier stability
        - Continuous component stress
    - Measurements:
        - A. Vin Average, old battery
        - B. Vin PP voltages, old battery
        - C. Peak Switching inductor current, new battery
        - D. Input capacitor RMS current, new battery
3. Idle to Playback at 80% volume
    - Informs:
        - Input Bulk capacitor current stress
        - Battery stress
        - Regulator/load-step recovery time
        - Switching inductor current stress
    - Measurements:
        - Peak transient current at battery and input capacitor
            A/B. new
            C/D. moderately used battery
        - Load-step peak (min) transient current magnitude and recovery time to loaded steady state at battery and input bulk capacitor
            E/F. new
            G/H. moderately used battery
        - I. Load-step peak (min) [voltage sag, recovery time to loaded steady state] (brackets), at battery, old battery
        - Peak switching inductor current
            J. new battery
            K. moderately used battery

Input capacitor stress:
- 1B, 1D, 2D, 3B, 3D

Based on the tabulated results in findings.ods, steady-state input ripple is the only improvement significant enough to drive the capacitor selection. Based on those results, a 10uF capacitor is chosen due to diminishing returns beyond that value, as a 47 uF capacitor will have only about 12mVPP lower than a 10uF capacitor and will also have an increased startup delay, with 5.76 ms at 10 µF versus 24.2 ms at 47 µF. Additionally, larger capacitances will generally require larger components.

The maximum current seen at the switching inductor of 2.44A is observed in the transition from idle to playback. This is well below the saturation current listed in the datasheet of 7.4A and is deemed acceptable.
