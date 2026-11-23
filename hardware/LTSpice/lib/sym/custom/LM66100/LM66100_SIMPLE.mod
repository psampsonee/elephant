* ------------------------------------------------------------
* LM66100_SIMPLE
* Pins: VIN VOUT CE ST G
*
* Simplified behavioral model:
*   - CE comparator with hysteresis
*   - Forward RON
*   - Ideal reverse blocking
*   - Optional turn-on / turn-off delay
*   - Open-drain ST output
* ------------------------------------------------------------

.subckt LM66100_SIMPLE VIN VOUT CE ST G
+ params: RON=140m TON=0 TOFF=0
+ VON=-150m VOFF=35m RST=100

* CE comparator state:
* ON if CE-VIN < VON
* OFF if CE-VIN > VOFF
* retain previous state inside hysteresis band
B_EN_RAW EN_RAW G V=
+ if(V(CE,G)-V(VIN,G)<VON, 1,
+ if(V(CE,G)-V(VIN,G)>VOFF, 0,
+ V(EN,G)))

* Optional switching delay
B_EN EN G V=
+ if(V(EN_RAW,G)>0.5,
+ delay(V(EN_RAW,G),{TON}),
+ delay(V(EN_RAW,G),{TOFF}))

* Ideal-diode forward path
B_PASS VIN VOUT I=
+ if(V(EN,G)>0.5,
+ max(V(VIN,VOUT),0)/{RON},
+ 0)

* ST open drain:
* channel ON  -> high impedance
* channel OFF -> pulled low
B_ST ST G I=
+ if(V(EN,G)>0.5,0,V(ST,G)/{RST})

.ends LM66100_SIMPLE
