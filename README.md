# Elephant

This project is intended to be a low-power audio player for a stuffed animal. The goal is to make a box that goes into a stuffed animal that takes up minimal space and lasts as long as possible on a single battery. The box should make an animal noise when its shaken, but only after some time has elapsed since the last time it has made a noise. The noise should be audible in a quiet room and should be immediately recognizable as a particular animal - in this case, an elephant. When the box has just been shaken, it will count - with very little power - a certain amount of time, then after that, wait to be shaken. Then, if you don't shake it, it should sit there, sipping very little power. When you do, it should make the animal noise within some amount of time (maybe a few fractions of a second).

## Power Budget / Battery Life

The board will have three main power states, corresponding to the three states of the state machine:

- Low-power
    - In this state, the STM32 is in standby mode. Everything but the backup domain - that is, the RTC and the backup registers - is powered off. Due to the quiescent currents of various devices during this state, it is expected that a little under 1 uA of current will draw from the main batteries.
- Buck Converter Off
    - The STM32 backup domain is powered only from its VBAT pin by the CR-2032 coin cell. Only the RTC and the backup registers are powered. This allows the STM32 to retain an accurate representation of the time. This will draw up to 2 uA from the CR-2032. However, testing will need to be done to verify this current consumption with the RTC in its particular configuration.
    - In this state, the buck converter becomes the predominate power sink for the main batteries, drawing 1 uA of current while shut down.
- Play Sound (highest power)
    - The microcontroller and DAC/amplifier (SSM2518) are both active, and the SSM2518 draws most of the current. This state will last for a few seconds, but contributes to a significant amount of the energy consumption of the main batteries. The LT-8640 will be supplying roughly 3.7W in this state and drawing 0.41A from the battery.


## State Machine

This firmware uses the Gang-of-Four State pattern: Elephant is the Context and each concrete state implements enter/toggle/exit. Each state is exposed via a singleton instance (no per-state heap allocations); any per-device data lives in the Elephant object. Interrupt service routines are kept tiny — they set flags or enqueue events — and the main loop/state handlers process those events and perform transitions, ensuring deterministic, non-blocking behavior. See notes in the README about concurrency (brief critical sections) and buffer sizing (samples vs bytes) (TODO).

The states in the state machine will correspond to each of the states mentioned in the **Power Budget / Battery Life** section above, with the following transition causes and tasks:

- Light Sleep
    - Upon waking up from standby, the firmware will detect why was reset (confirm entering standby), and why it woke (confirm RTC alarm) in main(). Once the STM32 is in this state, the STM32 will be in standby mode, corresponding to the "Low-power" power state.
    - Transitions to Deep Sleep when real time clock alarm fires. When the alarm fires, the STM32 briefly powers on completely to do the transition. During this transition, the microcontroller must save any data that needs to be retained (probably: last sound played (avoid repetition) and any state information needing to be retained) to spare backup registers, then pull the *GPIO_pwr_buck_off* pin low, triggering the 74AUP1G74 to clear, tying the LT8640 EN/UV pin low and causing it to power down.
- Deep Sleep
    - This state never sees a transition to another state in the code as the STM32 is completely powered off during it. Instead, the transition from this state occurs when the STM32 powers back on due to the LT8640 restoring power to the board. Corresponds to **Buck Converter Off**
    - "Transitions" to Play Sound when the tilt switch pulls the preload pin of the 74AUP1G74 low briefly, pulling Q high and turning the LT8640 back on.
- Play Sound
    - Upon powering on, the firmware will detect why was reset (POR), and why it woke (power restored) in main().  In this state, the STM32 will prepare the EEPROM for reading, then load data from the EEPROM in packets while playing a sound through the Audio object. Corresponds to the power state of the same name.
    - Transitions to Light Sleep when the Audio object completes playing a sound. During this transition, the STM32 sets an alarm 4 hours ahead of the current time to trigger it to wake up and transition into deep sleep.


## Choice of Components

### LT8640 Buck Converter

The LT8640 was chosen due to its high efficiency and ability to be turned off via the enable pin, which takes very little current to drive and allows the battery to be **practically** disconnected from the circuit (x nA is expected to leak while the LT8640 is turned off).

### STM32F401CCU Microcontroller

- Powerful enough to play intelligible audio
- Low-power options allow for RTC battery backup and external wakeups
- Nearly the same chip as on a "Black Pill" (For development)

### M95M04 EEPROM

- 4 Mbit is enough for several audio files (show calcs)
- Low Power
- 200 year data retention - not an SD card

### SSM2518 I2S DAC and amplifier

- Low quiescent current
- A one-chip solution to audio (maybe I dont need to say this in the final readme)
- Powerful enough to be heard at 2W per channel
-Very low noise

### LM66100 ideal diodes (power source OR-ing)

- Low quiescent (0.3uA) and leakage (max 600nA at operating temperature) currents
- Actively controlled PFET limits reverse-current to nanoamps. This is especially important for the coin cell to avoid damage, especially in high-temperature environments where a BAT54 could cause a failure in low-power mode.
- LM66100 ideal diodes were selected for power-source OR-ing due to their low quiescent current and low reverse leakage; reverse-current behavior into the coin cell is still being validated in simulation.

## Next Steps

## Risks and Unknowns