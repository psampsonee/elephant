# Relevant Design Questions
1. What seams exist at source-transition and what are their worst-case conditions?
    A. What is the minimum VBackup voltage during handoff?
2. What are the worst-case leakage currents of the power-or network?
3. What are the worst-case transient and steady-state currents which could contribute to thermal load?
    - Particularly, worst-case capacitor charge inrush current.
4. What are the failure modes for this configuration?
    A. What happens if no coin cell is installed?
    B. Does a decaying buck output produce brownout or chatter?
    C. Any leakage through GPIOs when VDD=0?
    D. What happens when the backup node is shorted?
    E. What happens when the coin cell is reversed?
    F. What happens when the buck converter rail is shorted?
    G. What happens when the coin cell is at end of life?
    H. What does a replaced coin cell transient current look like when backup cap is discharged?
    I. What are the worst-case temperature conditions in regards to reverse leakage and FET behavior (hot AND cold)?
    J. What happens when one or both of the ideal diodes are shorted?
5. What is an acceptable VBackup capacitance?
    A. Start with 1uF and change if needed.
6. What happens during main power startup?
    A. Is voltage overshoot within an acceptable range?
    
# Simulations

- Handoff: Buck -> Coin cell
    - Model coin cell internal resistance
    - Check transient currents and backup cap discharge
    - Check diode states for chatter
    - Check backup voltage for brownout condition - Drives capacitance
- Handoff: Coin cell -> Buck
    - Check for voltage overshoot
    - Check for reverse transient current to coin cell
- Buck power off: reverse leakage to powered-off buck converter rail.
- Steady state, buck on: reverse leakage to coin cell
- Brand new coin cell transient: maximum current
- Failure conditions:
    - Backup battery reverse voltage
    - Backup node short
    - No backup battery
    - 2VDC buck voltage
    - Shorted ideal diode(s)
- Source crossover (Vbuck ~= Vcoin); buck sweeps slowly. Exposes partial diode conduction, source sharing, or chatter.
