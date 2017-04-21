# Atari 2600 Emulator

This is an Atari 2600 emulator currently under development in C.

## Currently Implemented:

6502 CPU Registers  
* A - Accumulator
* X - Index Register
* Y - Index Register
* PC - Program Counter
* S - Stack Pointer
* P - Process Status Register
    * Bit 0 - C - Carry
    * Bit 1 - Z - Zero
    * Bit 2 - I - IRQ Disable
    * Bit 3 - D - Decimal Mode
    * Bit 4 - B - Break Flag
    * Bit 5 - 1 - Not used
    * Bit 6 - V - Overflow
    * Bit 7 - N - Negative/Sign

`tick()` function to handle the discrepancy between 1.19Mhz 6502 processor and several Ghz modern processors.

Handles illegal and undefined opcodes.

Opcode matrix declaration.

2-byte memory addressing.

The following opcodes:
* TAY
* TAX
* TSX
* TYA
* TXA
* TXS
* LDA (Mostly)

## To be Implemented:

The rest of the opcodes.

Memory and I/O Map

Memory Mirrors

Video

Interval Timer

Audio

Input

Reading from a ROM File

(optional) Actual programming of illegal opcodes

## Usage and Compilation

As of right now, the Atari 2600 Emulator is in an extremely early stage of development.
As such, it does not even have a `main()` function. Therefore, you may attempt to compile,
but doing so would most likely be superfluous. By extension, there is, as of yet, no known
means of using the Atari 2600 Emulator.

If you must use it, the proper manner, insofar as there may or may not be one, is:
    
    vim a2600.c
