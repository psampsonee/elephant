; --- target operating point ---
.param VREG=3.3

; --- LT8640 Test Conditions ---

.param V_BUCK=3.3
.param R_BUCK=1
.param L_BUCK=500n


; --- CR2032 Battery Test Conditions (Energizer) ---

.param V_COIN=3.0 ; 2.4-3 volts
.param R_COIN=5 ; 5-20 ohms
.param L_COIN=500n

; --- timing ---
.param T_EN=5m
.param T_START_END=15m
.param T_WORST=20m

; --- edge smoothing ---
.param TR=10u

; - Component Values -

; -- Nominals --

.param R_ST_PRIORITY_NOM=2M
.param R_ST_SECONDARY_NOM=1M
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
