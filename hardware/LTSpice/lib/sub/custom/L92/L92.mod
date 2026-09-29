; ============================================================
; AAA battery model - Energizer L92
;
; Global expected:
;   .include L92_params.inc
;
; Instance example:
;   XBAT BAT+ 0 AAA_BATTERY MAH_INIT=0 L_SER=20n Q_EOL=1284
; ============================================================

.subckt AAA_BATTERY_L92 P N params: MAH_INIT=0 L_SER=20n Q_EOL=1284

; ------------------------------------------------------------
; Clamped charge value (at 0)
; ------------------------------------------------------------
.func q_L92(q) {min(q,1284)}

; ------------------------------------------------------------
; Ideal cell voltage
; ------------------------------------------------------------
B_CELL n_cell N V={V_cell_L92(q_L92(V(mAh_used)))}

; ------------------------------------------------------------
; Capacity-dependent internal resistance
; ------------------------------------------------------------
R_INT n_cell n_r R={Rint_L92(q_L92(V(mAh_used)))}

; ------------------------------------------------------------
; Battery series inductance
; ------------------------------------------------------------
L_SERIES n_r n_sense {L_SER}

; ------------------------------------------------------------
; Zero-volt source for current measurement.
; Positive I(V_SENSE) = battery discharge current.
; ------------------------------------------------------------
V_SENSE n_sense P 0

; ------------------------------------------------------------
; Coulomb counter
;
; integral(A dt) / 3.6 = mAh
;
; max(...,0) prevents reverse current from decreasing mAh_used.
; ------------------------------------------------------------
B_MAH mAh_used 0 V={idt(max(I(V_SENSE),0)/3.6, MAH_INIT)}

.ends AAA_BATTERY_L92
