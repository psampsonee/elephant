# LSE Network Requirements
Startup time:
Drive level:

## Crystal
Maximum ESR: <= 1/3 of the STM32 negative transresistance
    - Rf=~10-25Mohm
Load Capacitance:
Shunt Capacitance:
Freq tolerance (25C):

## Capacitors
Capacitance:
Maximum ESR:

# HSE Network Requirements (pg.77)
Startup time:
Drive level:
Frequency: 26 MHz

## Crystal
Crystal Frequency:
Maximum ESR: <= 1/5 of the STM32 negative transresistance
    - Rf=~470k to 5Mohm
Load Capacitance:
    Use 10pF as a rough estimate of pin/board capacitance.
    The network caps are chosen to tune the load capacitance ot a specified value (Parallel equ+stray)
Shunt Capacitance:
Freq tolerance (25C):

## Capacitors
Capacitance: 5 pF to 25 pF range 
    (determined by specified crystal load capacitance, series combination of the capacitors)
Other notes: High quality, designed for high frequency

## Sources

https://www.st.com/resource/en/application_note/an2867-guidelines-for-oscillator-design-on-stm8afals-and-stm32-mcusmpus-stmicroelectronics.pdf

https://www.st.com/content/ccc/resource/technical/document/datasheet/9e/50/b1/5a/5f/ae/4d/c1/DM00086815.pdf/files/DM00086815.pdf/jcr:content/translations/en.DM00086815.pdf
