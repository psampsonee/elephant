# Buck Convertor Design Bibliography

## First Principles

Basic theory of operation: 
- https://www.allaboutcircuits.com/technical-articles/understanding-switch-mode-regulation-the-buck-converter/

Equations for non-isolated circuit in continuous-conduction mode: 
- Art of Electronics, 3rd Edition, by Paul Horowitz and Winfield Hill, 9.6.5 Step-down (buck) converter (pg. 644). 

## Major Datasheets

LT-8640A:
- https://www.analog.com/media/en/technical-documentation/data-sheets/lt8640a.pdf
    - Pg. 12 - Block Diagram
    - Pg. 14-22 - Applications Information
    - Pg. 23 - Relevant Typical Application (3.3V, 5A Step-Down Converter)

## Design Notes

1. See bib.ods for a full list of sources and parameters found on each source.
2. A reference circuit from the LT-8640A datasheet was used for the buck convertor design.
3. Minimum component tolerance factors are calculated with this formula: 1-Tol. %
