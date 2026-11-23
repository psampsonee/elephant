# Board Design Guidelines

## Dimensions

### Constraints

AAA Battery Holder Dimensions: 2.087" L x 1.957" W
Board Edge Clearances:
    Outer Copper: 10 mil
    Inner copper: 20 mil
    Components: 200 mil
    Holes: 1 screw diameter
Minimum board area / sum component areas: 2.5
Minimum board area: 7.09 in^2

-> Given these constraints, usable board dimensions will be 1.9"x3.75" and total board dimensions will be 2.3"x4.15".

## Layer Stack
1. Top Signal
2. GND
3. PWR
4. Bottom Signal

## Component Placement Priorities

### Mechanical
0. Mounting Holes
1. Coin Cell
2. AAA Battery Jumper
3. Speaker Headers
4. Debug Headers
5. Tilt Switch

## Electrical
A. Buck converter - Switching loop geometry
B. STM32 - with crystals and decoupling caps
C. Power-OR - Relative to buck output, backup, MCU supply
D. Audio Amp - with attention to I2S routing and speaker connections

## Mounting holes
On the four corners, with 200mil clearance from board edge and components.

## Trace Ampacities

For main battery supply lines, 1A > 0.55A
    Traces: 12 mils or 20 mils
    Vias: 2x 0.3mm
For buck output / amp power input lines, 2A > 0.85A
    Traces: 40 mils
    Vias: 3x 0.3mm
All other lines, < 300mA
    Traces: 8 mils or 10 mils
    Vias: 1x 0.3mm

- These trace widths apply to external 1 oz copper. Internal power distribution uses appropriately sized copper pours.
- Check voltage drop on longer power routes, particularly the 3.3 V rail.
