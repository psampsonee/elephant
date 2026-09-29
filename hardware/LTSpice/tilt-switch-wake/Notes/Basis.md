# RC Time Constant Basis

## Experimentally derived variables

### STM32F401CU (Scope)

Minimum MCU supply voltage for GPIO assertion: 1.73V
Minimum time to assert GPIO: 5.69ms

### LT8640A-3.3

Output voltage: 3.3V
Time to reach minimum boot voltage (1.8V): 3.07ms (simulation result)

## Datasheet Variables:

LT8640 EN voltage: 1V
LT8640 EN hysteresis: 40mV

## Assumed / calculated variables

Minimum RC time above EN threshold: (5.69+3.07)*1.2=~10.5ms
Maximum RC charge voltage (90% of 90% of 3.3V): 2.67V
Discharging RC time constant (t1 = 10.5ms, V1 = 0.96V, V0 = 2.67V): -(t1/(ln(V1/V0)))=10.27ms
-> Given C=22nF, R=~600k

## Nominal charging and discharging characteristics

Based on this datasheet:
https://signalquest.com/wp-content/uploads/Tilt-and-Vibration-Sensor-SQ-SEN-200.pdf?srsltid=AfmBOop8h36hEv8tVrpdrmafd0xrNLEwCzAzqTTlbAF32Pdq68Qd7nw_

According to the vibration characteristic curve, assuming that either low-to-high or high-to-low counts as a transition, the estimated average closed-contact duration at \(D_{\max}\) is:

{2*D_max/(N_transitions|D_max)} ~= {2*0.65/1100} ~= 1.18ms

Since we don't have a particular switch in mind at this time, and it must be normally open for the wakeup circuit we have in mind to work, we will assume:

1.18 ms is approximately 12× 0.1 ms

and use 0.1ms as the assumed minimum available charging pulse, pending verification with real hardware.

## Crude impulse sensor

To later add functionality to determine roughly how much effort was put into a shake, an NMOS inverter circuit will be used in the final hardware. This will be neglected in LTspice tests.
