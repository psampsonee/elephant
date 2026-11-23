; --- target operating point ---
.param VREG=3.3

; --- LT8640 Test Conditions ---

.param V_BUCK=3.3
.param R_BUCK=1
.param L_BUCK=500n
.param R_LOAD=100m


; --- CR2032 Battery Test Conditions (Energizer) ---

.param V_COIN=3.0
.param R_COIN=10
.param L_COIN=500n

; -- Timing --
.param T_COIN_STEP=1m
.param T_COIN_RAMP=1u

; -- Test functions --
.func V_COIN(t)={V_COIN*if(t<T_COIN_STEP,0,
    + if(t<T_COIN_STEP+T_COIN_RAMP,
         + (t-T_COIN_STEP)/T_COIN_RAMP,1))}

; - Component Values -

; -- Nominals --

.param R_ST_PRIORITY_NOM=2Meg
.param R_ST_SECONDARY_NOM=1Meg
.param C_VBACKUP_NOM=1u

; -- Worst-Case Tolerance Factors --

.param R_ST_PRIORITY_TOL_FACTOR=0.9
.param R_ST_SECONDARY_TOL_FACTOR=0.9
.param C_VBACKUP_TOL_FACTOR=0.9

; -- Component Derating Factors --

.param C_VBACKUP_DC_BIAS_FACTOR=0.6

; -- Component Test Values --

.param R_ST_PRIORITY={R_ST_PRIORITY_NOM*R_ST_PRIORITY_TOL_FACTOR}
.param R_ST_SECONDARY={R_ST_SECONDARY_NOM*R_ST_SECONDARY_TOL_FACTOR}
.param C_VBACKUP={C_VBACKUP_NOM*C_VBACKUP_TOL_FACTOR*C_VBACKUP_DC_BIAS_FACTOR}
