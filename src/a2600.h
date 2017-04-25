#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "CPUMemRegTrans.h"
#include "CPUArithLogOps.h"
#include "CPURotShift.h"
#include "CPUJumpCtrl.h"

#ifndef A2600_H_
#define A2600_H_

// ................................................................................................
// 65XX CPU
// ................................................................................................
//Registers
//General Purpose:
uint8_t A;      //Accumulator
uint8_t X;      //Index Register X
uint8_t Y;      //Index Register Y
//
uint16_t PC;    //Program Counter
//Addresses 256 bytes in page 1 of memory [0x00, 0xFF]
//Points to the first FREE byte on the stack
//So, should be initialized to S=(1)0xFF, rather than S=(2)0x00
uint8_t S;      //Stack Pointer
uint8_t P;      //Processor Status Register
//Processor Status Register:
//Bit   Name    Expl.
//0     C       Carry           (0=No Carry, 1=Carry)
//1     Z       Zero            (0=Nonzero, 1=Zero)
//2     I       IRQ Disable     (0=IRQ Enable, 1=IRQ Disable)
//3     D       Decimal Mode    (0=Normal, 1=BCD Mode for ADC/SBC opcodes
//4     B       Break Flag      (0=IRQ/NMI, 1=RESET or BRK/PHP opcode)
//5     -       Not used        (Always 1)
//6     V       Overflow        (0=No Overflow, 1=Overflow)
//7     N       Negative/Sign   (0=Positive, 1=Negative)
//
//More info:
//Carry Flag:
//When used for subtractions, the carry flag has opposite meaning as for normal x86 and z80 CPUs.
//ie. it is SET when above-or-equal. For all other instructions, it works as normal,
//although ROL/ROR are rotating <through> carry
//Zero Flag:
//Z is set when result (or destination register, in case of some 'move' instructions) is zero
//Negative/Sign Flag:
//N is set when signed (ie. same as Bit 7 of rsult/destination)
//Overflow Flag:
//V is set when an addition/subtraction exceeded the maximum range for signed numbers [-128,+127]
//IRQ Disable Flag:
//Disables IRQs when set. NMIs and BRK instructions cannot be disable.
//Decimal Mode Flag:
//Packed BCD mode (range [0x00,0x99]) for ADC and SBC opcodes.
//Break Flag:
//Intended to separate between IRQ and BRK which are both using the same vector, [0xFFFE].
//Cannot be accessed directly, but there are 4 which are writing the P register to stack,
//which allows them to examine the B-bit in the pushed value: The BRK and PHP opcodes always
//write "1" into the bit, IRQ/NMI execution always write "0".

int8_t tick(uint8_t cycles);

// ................................................................................................
// ILLEGAL AND UNDEFINED OPCODES
// ................................................................................................
uint8_t ill(uint8_t op, uint8_t arg0, uint8_t arg1);
uint8_t und(uint8_t op, uint8_t arg0, uint8_t arg1);

// ................................................................................................
// OPCODE TABLE
// ................................................................................................
// Points to functions representing Assembly Pneumonics
// Found in other Files
uint8_t (*ops[16][16])(uint8_t op, uint8_t arg0, uint8_t arg1) = {
    {BRK, ORA, ill, und, ill, ORA, ASL, und, PHP, ORA, ASL, ill, ill, ORA, ASL, und},
    {BPL, ORA, ill, und, ill, ORA, ASL, und, CLC, ORA, ill, und, ill, ORA, ASL, und},
    {JSR, AND, ill, und, BIT, AND, ROL, und, PLP, AND, ROL, ill, BIT, AND, ROL, und},
    {BMI, AND, ill, und, ill, AND, ROL, und, SEC, AND, ill, und, ill, ADC, ROR, und},
    {RTI, EOR, ill, und, ill, EOR, LSR, und, PHA, EOR, LSR, ill, JMP, EOR, LSR, und},
    {BVC, EOR, ill, und, ill, EOR, LSR, und, CLI, EOR, ill, und, ill, EOR, LSR, und},
    {RTS, ADC, ill, und, ill, ADC, ROR, und, PLA, ADC, ROR, ill, JMP, ADC, ROR, und},
    {BVS, ADC, ill, und, ill, ADC, ROR, und, SEI, ADC, ill, und, ill, ADC, ROR, und},
    {ill, STA, ill, ill, STY, STA, STX, ill, DEY, ill, TXA, ill, STY, STA, STX, ill},
    {BCC, STA, ill, ill, STY, STA, STX, ill, TYA, STA, TXS, ill, ill, STA, ill, ill},
    {LDY, LDA, LDX, ill, LDY, LDA, LDX, ill, TAY, LDA, TAX, ill, LDY, LDA, LDX, ill},
    {BCS, LDA, ill, ill, LDY, LDA, LDX, ill, CLV, LDA, TSX, ill, LDY, LDA, LDX, ill},
    {CPY, CMP, ill, und, CPY, CMP, DEC, und, INY, CMP, DEX, ill, CPY, CMP, DEC, und},
    {BNE, CMP, ill, und, ill, CMP, DEC, und, CLD, CMP, ill, und, ill, CMP, DEC, und},
    {CPX, SBC, ill, und, CPX, SBC, INC, INC, INX, SBC, NOP, ill, CPX, SBC, INC, und},
    {BEQ, SBC, ill, und, ill, SBC, INC, und, SED, SBC, ill, und, ill, SBC, INC, und}
};


// ................................................................................................
// MEMORY I/O
// ................................................................................................


uint8_t MEMORY[0x10000];
// Put an abstraction layer on the MEMORY, because IO Ports are also part of the memory space;
uint8_t read(int ind);
void write(int ind, uint8_t val);
//0000-002C     TIA Write
//0000-000D     TIA Read            (sometimes mirrored at 0030-003D)
//0080-00FF     PIA RAM             (128 bytes)
//0280-0297     PIA Ports and Timer
//F000-FFFF     Cartridge Memory    (4 Kbytes area)


#endif
