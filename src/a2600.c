#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "CPUMemRegTrans.h"
#include "CPUArithLogOps.h"
#include "CPURotShift.h"
#include "CPUJumpCtrl.h"
#include "a2600.h"


int8_t tick(uint8_t cycles)
{
    // The Atari 2600 contains a 1.19 Mhz 65xx Processor
    // That means that each clock cycle takes 840 nanoseconds, so do that.
    long ns = cycles * 840;
    struct timespec delay = {0, ns};
    return nanosleep(&delay, NULL);
}

// ................................................................................................
// ILLEGAL AND UNDEFINED OPCODES
// ................................................................................................
uint8_t ill(uint8_t op, uint8_t arg0, uint8_t arg1)
{
    fprintf(stderr, "%s\n", "Illegal Opcode Called, may be implemented in the future for completeness");
    return 1;
 // exit(1);
}

uint8_t und(uint8_t op, uint8_t arg0, uint8_t arg1)
{
    fprintf(stderr, "%s\n", "Undefined Opcode Called");
    return 1;
 // exit(1);
}

// ................................................................................................
// OPCODE TABLE
// ................................................................................................
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
// Initialize CPU to Default Values
// ................................................................................................
int initCPU()
{
    A = 0;
    X = 0;
    Y = 0;
    PC = 0xF000;
    S = 0xFF;
    P = 0x20;
}

// ................................................................................................
// MEMORY I/O
// ................................................................................................

uint8_t read(int ind)
{
    switch(ind)
    {
    default:
        return MEMORY[ind];
        break;
    }
}
void write(int ind, uint8_t val)
{
    switch(ind)
    {
    default:
        MEMORY[ind] = val;
        break;
    }
}
