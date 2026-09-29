; - Test-Specific Parameters -

; -- Test Conditions --

.param V_IN_NOM=3.3V
.param V_IN_TOL_FACTOR=0.9
.param V_IN={V_IN_NOM*V_IN_TOL_FACTOR}

.param T_SW_PULSE=0.1ms ; assumed minimum available charging pulse

.param V_THRESH_RISING=1.04
.param V_THRESH_FALLING=0.96

.param R_EN_LT8640=100M ; to achieve passable EN pin leakage behavior

; -- Test functions --
.func I_SW(t) {if(t<(1u+T_SW_PULSE) & t>=1u,(V_IN-V(V_RC))/R_CHARGE,0)}

; -- Component Values --

; --- Nominal Values ---

.param C_CHARGE_NOM=22n
.param R_DISCH_NOM=600k

; --- Worst-Case Tolerance Factors ---

.param R_DISCH_TOL_FACTOR=0.9
.param C_CHARGE_TOL_FACTOR=0.9

; --- Derating Values ---

.param C_CHARGE_DC_BIAS_FACTOR=0.8 ; Part not chosen; provisional

; --- Parasitic Values ---

.param R_CHARGE = 10 ; Upper bound for resistance from voltage source to capacitor
.param R_GPIO_LEAKAGE=10M ; Rough effective GPIO impedance for leakage/backpowering sensitivity check

; --- Component Test Values ---

.param C_CHARGE={C_CHARGE_NOM*C_CHARGE_TOL_FACTOR*C_CHARGE_DC_BIAS_FACTOR}
.param R_DISCH={R_DISCH_NOM*R_DISCH_TOL_FACTOR}
