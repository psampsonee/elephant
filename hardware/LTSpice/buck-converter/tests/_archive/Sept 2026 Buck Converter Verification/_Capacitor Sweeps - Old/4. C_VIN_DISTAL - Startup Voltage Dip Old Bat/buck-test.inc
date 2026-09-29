
; --- Test Initial Conditions ---
.param I_L_SW_INIT=0 ; Baseline steady-state = 0
.param V_COUT_INIT=0 ; Baseline steady-state = 3.3225

; --- Test Values ---
.param V_AAA 1.2
.param MAH_USED=1270
.param V_EN=1
.param V_LOAD_NOM=3.3
.param P_LOAD=154u ; Watts, steady-state during playback.
.param R_LOAD={V_LOAD_NOM*V_LOAD_NOM/P_LOAD}

; --- Model Parameters ---

; ------------------------------------------------------------
; L92 Internal resistance vs. discharged capacity [mAh]
; ------------------------------------------------------------
.func Rint_L92(q) table(q, 0,0.32, 9,0.28, 40,0.25, 101,0.23
+ 187,0.22, 294,0.21, 403,0.21, 484,0.21, 804,0.19
+ 1025,0.20, 1122,0.21, 1150,0.22, 1169,0.22, 1187,0.23
+ 1200,0.24, 1210,0.25, 1221,0.27, 1232,0.30, 1246,0.38
+ 1262,0.58, 1279,0.79)

; --- Sweep ---
.step param C_VIN_DISTAL_NOM list 100n 4.7u 10u 22u 47u
; .step param BAT_INDEX list 1 2 3 4 -->
; .param V_AAA table (BAT_INDEX, 1, 1.55, 2, 1.4, 3, 1.3, 4, 1.2) -->
; .param MAH_INIT_SWEEP table (BAT_INDEX, 1, 0, 2, 700, 3, 1200, 4, 1270) -->

; -- Component Values (Note 1) --

; --- Capacitor Voltage Ratings ---
.param C_OUT_VOLTAGE_RATING=16
.param C_1U_VOLTAGE_RATING=50

; --- Capacitor Voltage Derating Factors ---
.param C_OUT_VOLTAGE_DERATING_FACTOR=0.8

; --- Testing Target Values From Datasheets ---
.param L_SW_I_SAT=7.4
.param C_OUT_V_MAX={C_OUT_VOLTAGE_RATING*C_OUT_VOLTAGE_DERATING_FACTOR}

; --- Nominal Component Parameters ---
.param C_1U_NOM=1u
.param C_TRSS_NOM=10n
.param R_RT_NOM=17.8K
.param L_SW_NOM=2.2u
.param C_OUT_NOM=100u

; --- Component Tolerances ---
.param C_VIN_DISTAL_MIN_TOL_FACTOR=0.8 ; Provisional (no part chosen)
.param C_VIN_LOCAL_MIN_TOL_FACTOR=0.8
.param C_1U_MIN_TOL_FACTOR=0.9
.param C_TRSS_MIN_TOL_FACTOR=0.9
.param R_RT_MIN_TOL_FACTOR=0.99
.param L_SW_MIN_TOL_FACTOR=0.7
.param C_OUT_MIN_TOL_FACTOR=0.8

; --- Capacitor DC Biases ---
.param C_VIN_DISTAL_DC_BIAS_FACTOR=0.95 ; Provisional (no part chosen)

; --- Component Test Values ---
.param C_VIN_DISTAL={C_VIN_DISTAL_NOM*C_VIN_DISTAL_MIN_TOL_FACTOR*C_VIN_DISTAL_DC_BIAS_FACTOR}
.param C_1U={C_1U_NOM*C_1U_MIN_TOL_FACTOR}
.param C_TRSS={C_TRSS_NOM*C_TRSS_MIN_TOL_FACTOR}
.param R_RT={R_RT_NOM*R_RT_MIN_TOL_FACTOR}
.param L_SW={L_SW_NOM*L_SW_MIN_TOL_FACTOR}
.param C_OUT={C_OUT_NOM*C_OUT_MIN_TOL_FACTOR}

; ---- Bias Circuit (Internal to 3.3V variant of LT8640) ----
.param C_BIAS=4.7p
.param R_BIAS_1=1Meg
.param R_BIAS_2=412K

; --- Nonideal Parameters ---
.param R_AAA=270m
.param L_AAA=500n
.param DCR_L_SW_WORST=13m
.param ESR_C_OUT=50m ; at 100kHz
.param ESR_C_1U=11.01m
.param ESL_C_1U=224.594p

; Notes
; 1. Sources for component values can be found in notes/bib.ods
