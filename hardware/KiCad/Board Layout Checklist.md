# Board Layout Checklist

## Pre-Layout
Determine:
- [x] Board edge clearances
- [x] AAA Battery holder dimensions (board form factor consideration)
- [x] Board dimensions
- [x] Number of board layers and their functions
- [x] Component placement priorities
- [x] Mounting hole locations
- [x] Speaker mounting method (to enclosure)
- [x] Tilt switch orientation to achieve intended behavior
- [x] Identify critical current loops, sensitive signals, and their required placement/routing constraints.
- [x] Determine whether buck converter layout can substantially match the recommended layout
- [x] Power trace and via sizes appropriate for loads
- [x] Power regions (9v, Vbuck, Vbackup).
- [x] Configure KiCad DRC to meet JLCPCB capabilities

## During Layout
Ensure that:
- [x] A continuous ground return path is maintained beneath critical signal routes
- [x] Ground stitching vias are placed around signals crossing layers.
- [x] Power traces and vias are sized to specifications previously determined
- [x] STM32 pin assignments are reasonably close to the peripherals they are intended to serve.
- [x] HSE/LSE crystal traces are as close to chip as possible.
- [x] C_NRST is placed as close to the STM32 as possible.
- [x] Small decoupling capacitors are as close as possible to the pins they serve for each IC
- [x] Large decoupling capacitors are close to the pins they serve for each IC
- [x] Audio amp speaker traces are short and do not cross sensitive signal traces
- [x] Tilt switch has clearance on all sides for 90-degree orientation (keep-out)

## Pre-fabrication checklist

### CAD inspection
Check:
- [x] DRC passes
- [x] Component clearances (height) are reasonable for intended enclosure dimensions (what are these dimensions?)
    -> Ignore for Rev A; keep for Rev B.
- [x] Coin cell is placed sufficiently close to board edge for replacement
- [x] Coin cell has sufficient clearance from other components for replacement
- [x] Test points are accessable (components do not block)
- [x] C_NRST is placed as close to the STM32 as possible.

### Gerber / 3D visualization inspection
Visual inspection for correctness:
- [x] Board outline is present and correct
- [x] Copper layers and solder mask look correct
- [x] Silkscreen is not clipped / obscures exposed pads
- [x] Drill holes, mounting holes are present
- [x] No layers are missing / accidently mirrored
- [x] (3D) Visual inpsection for test point access

### Final pre-fab checks
- [x] DRC passes
- [x] Verify schematic-PCB parity
