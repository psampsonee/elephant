# Rationale

This test is intended to determine whether the worst-case conditions of the backup node in the event of a source transition from the buck converter to the coin cell are sufficient to maintain power to downstream devices.

Specifically:
- Voltage sag (Depleted-cell)
- coin cell peak current (new cell)
- backup capacitor current (new cell)
- Transient duration
- Ideal-diode states (ST pins)

Worst-case corners:
- Depleted-cell corner: 2.0V, 100 ohms source resistance, selected as a conservative funcitonal test condition rather than a guaranteed datasheet limit.
- New-cell corner: 2.9V, 8 ohms source resistance
- LM66100 on-resistance is not the dominant source-resistance in the model and is kept at the default 140mohms.
