## Questions

1. With worst-case maximum switch-closure duration, component values and parasitics, how does the RC node charge?
2. What maximum voltage does the RC node reach under the worst-case closure?
Sweeps:
    - N/A
Measurements:
    - Maximum RC and EN node voltages
3. What is the minimum time that the EN node remains above threshold voltage (0.96V) during discharge?
4. How does GPIO interact with the tilt switch circuit?
    - Leakage current during discharge
    - backpowering
5. What is the worst-case leakage current from the tilt switch circuit while the buck converter is off?
    - With the tilt switch open, the always-on 3.3 V source has no intended DC path into the circuit. Remaining current is limited to physical open-switch leakage, expected to be negligible (nA-scale). No further simulation required.

## Simulations

1. Charging - Answers 1 and 2
2. Discharge / hold time - Answers 3

## Answers

1. RC charging is effectively instantaneous relative to the minimum assumed switch-closure duration.
2. 
    A. Maximum RC node voltage: 2.97V
    B. Maximum EN node voltage: 2.86V
3. Minimum time above threshold: 12.0ms
4. Open switch creates no meaningful off-state leakage path.
5. GPIO clamp/backfeed behavior is negligible in the modeled transient.
