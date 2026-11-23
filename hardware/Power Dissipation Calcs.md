# Power Dissipation Calcs

1. LT8640
Operating point: Vin = 6V, Vout = 3.3V, IOut~=5.5W/3.3V~=1.7A, f_SW=2MHz
Datasheet basis: G02 is conservative 12V input condition
Estimated efficiency ~92%
Total converter loss: 0.5W
Thermal asusmption: Conservatively treat all converter loss as LT8640 dissipation.
Thermal resistance: Theta_JA=40C/W
Ambient temperature assumption:40C
Estimated junction temperature: ~60C
Limit: T_J,max=125C
Conclusion: Large thermal margin; no further thermal analysis required.

2. LM66100
Operating point (Both): Vin=3.3V, I_RMS~=I_DC (for simulation purposes)~=(3.3V/590kOhm)=6uA
Datasheet basis: Typical on-impedance: 140mOhm
Estimated power dissipation: 6uA^2*140mOhm=4.4pW

Normal operating current is on the order of 6uA conduction loss is negligible. No thermal concern identified.

3. Resistors

The largest non-zero-ohm resistor current in the power section is the status LED resistor (330 ohm), which recieves 10mA of current. At 3.3V, this corresponds to 33mW of power dissipation, well below the power dissipation rating of 0.125W.

4. SSM2518

Vin=3.3V Iin=0.25A
Junction thermal resistance (datasheet) = 54C/W
Efficiency=77% at 3.6V supply and 0.8W combined output power
Heat loss=(1-0.77)*(0.25*3.3)=0.18975W
Thermal assumption: Conservatively treat all heat loss as SSM2518 dissipation.
Ambient temp assumption=40C
Estimated junction temp: ~50.25C
T_J,max=165C
Max operating temp=85C
Conclusion: Large thermal margin; no further thermal analysis required. Verify worst-case supply current during hardware testing.
