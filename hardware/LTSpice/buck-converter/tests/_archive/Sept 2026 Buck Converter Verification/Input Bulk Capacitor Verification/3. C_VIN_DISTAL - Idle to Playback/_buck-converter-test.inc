; --- target operating point ---
.param VREG=3.3

; --- AAA Battery Test Conditions(L92) ---

.step param V_AAA list 1.3 1.5 1.7 param R_AAA list 0.23 0.27 0.31 0.35

; --- CR2032 Battery Test Conditions (Energizer) ---

.step param V_COIN list 2.5 2.8 3.0 param R_AAA list 20 40 100

; --- test currents ---
.param I_START=0.5
.param I_IDLE=0.11
.param I_WORST=0.5

; --- convert to equivalent resistances ---
.param R_START = VREG/I_START
.param R_IDLE  = VREG/I_IDLE
.param R_WORST = VREG/I_WORST

; --- timing ---
.param T_EN=5m
.param T_START_END=15m
.param T_WORST=20m

; --- edge smoothing ---
.param TR=10u
