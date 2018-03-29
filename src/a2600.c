#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "CPU65xx/CPUMemRegTrans.h"
#include "CPU65xx/CPUArithLogOps.h"
#include "CPU65xx/CPURotShift.h"
#include "CPU65xx/CPUJumpCtrl.h"
#include "a2600.h"
#include "clock.h"


int8_t tick(uint8_t cycles)
{
//  // The Atari 2600 contains a 1.19 Mhz 65xx Processor
//  // That means that each clock cycle takes 840 nanoseconds, so do that.
//  long ns = cycles * 840;
//  struct timespec delay = {0, ns};
//  return nanosleep(&delay, NULL);
    // New system, probably going to end up removing cycles.
    for(int i = 0; i < cycles; ++i)
    {
        while(!CPUTick);    // Wait for a signal from clock thread
        CPUTick = 0;        // Reset signal
    }
}

// ................................................................................................
// ILLEGAL AND UNDEFINED OPCODES
// ................................................................................................
uint8_t ill_op(uint8_t arg0, uint8_t arg1)
{
    fprintf(stderr, "%s\n", "Illegal Opcode Called, may be implemented in the future for completeness");
    return 1;
 // exit(1);
}

uint8_t und_op(uint8_t arg0, uint8_t arg1)
{
    fprintf(stderr, "%s\n", "Undefined Opcode Called");
    return 1;
 // exit(1);
}

// ................................................................................................
// OPCODE TABLE
// ................................................................................................
uint8_t (*ops[16][16])(uint8_t arg0, uint8_t arg1) = {
    {BRK_00, ORA_01, ill_op, und_op, ill_op, ORA_05, ASL_06, und_op, PHP_08, ORA_09, ASL_0A, ill_op, ill_op, ORA_0D, ASL_0E, und_op},
    {BPL_10, ORA_11, ill_op, und_op, ill_op, ORA_15, ASL_16, und_op, CLC_18, ORA_19, ill_op, und_op, ill_op, ORA_1D, ASL_1E, und_op},
    {JSR_20, AND_21, ill_op, und_op, BIT_24, AND_25, ROL_26, und_op, PLP_28, AND_29, ROL_2A, ill_op, BIT_2C, AND_2D, ROL_2E, und_op},
    {BMI_30, AND_31, ill_op, und_op, ill_op, AND_35, ROL_36, und_op, SEC_38, AND_39, ill_op, und_op, ill_op, ADC_3D, ROR_3E, und_op},
    {RTI_40, EOR_41, ill_op, und_op, ill_op, EOR_45, LSR_46, und_op, PHA_48, EOR_49, LSR_4A, ill_op, JMP_4C, EOR_4D, LSR_4E, und_op},
    {BVC_50, EOR_51, ill_op, und_op, ill_op, EOR_55, LSR_56, und_op, CLI_58, EOR_59, ill_op, und_op, ill_op, EOR_5D, LSR_5E, und_op},
    {RTS_60, ADC_61, ill_op, und_op, ill_op, ADC_65, ROR_66, und_op, PLA_68, ADC_69, ROR_6A, ill_op, JMP_6C, ADC_6D, ROR_6E, und_op},
    {BVS_70, ADC_71, ill_op, und_op, ill_op, ADC_75, ROR_76, und_op, SEI_78, ADC_79, ill_op, und_op, ill_op, ADC_7D, ROR_7E, und_op},
    {ill_op, STA_81, ill_op, ill_op, STY_84, STA_85, STX_86, ill_op, DEY_88, ill_op, TXA_8A, ill_op, STY_8C, STA_8D, STX_8E, ill_op},
    {BCC_90, STA_91, ill_op, ill_op, STY_94, STA_95, STX_96, ill_op, TYA_98, STA_99, TXS_9A, ill_op, ill_op, STA_9D, ill_op, ill_op},
    {LDY_A0, LDA_A1, LDX_A2, ill_op, LDY_A4, LDA_A5, LDX_A6, ill_op, TAY_A8, LDA_A9, TAX_AA, ill_op, LDY_AC, LDA_AD, LDX_AE, ill_op},
    {BCS_B0, LDA_B1, ill_op, ill_op, LDY_B4, LDA_B5, LDX_B6, ill_op, CLV_B8, LDA_B9, TSX_BA, ill_op, LDY_BC, LDA_BD, LDX_BE, ill_op},
    {CPY_C0, CMP_C1, ill_op, und_op, CPY_C4, CMP_C5, DEC_C6, und_op, INY_C8, CMP_C9, DEX_CA, ill_op, CPY_CC, CMP_CD, DEC_CE, und_op},
    {BNE_D0, CMP_D1, ill_op, und_op, ill_op, CMP_D5, DEC_D6, und_op, CLD_D8, CMP_D9, ill_op, und_op, ill_op, CMP_DD, DEC_DE, und_op},
    {CPX_E0, SBC_E1, ill_op, und_op, CPX_E4, SBC_E5, INC_E6, INC_E7, INX_E8, SBC_E9, NOP_EA, ill_op, CPX_EC, SBC_ED, INC_EE, und_op},
    {BEQ_F0, SBC_F1, ill_op, und_op, ill_op, SBC_F5, INC_F6, und_op, SED_F8, SBC_F9, ill_op, und_op, ill_op, SBC_FD, INC_FE, und_op}
};

// ................................................................................................
// Initialize CPU to Default Values
// ................................................................................................
int initCPU()
{
    done = 0;

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
