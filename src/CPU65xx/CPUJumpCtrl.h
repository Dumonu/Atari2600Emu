#ifndef CPUJUMPCTRL_H_
#define CPUJUMPCTRL_H_

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// .................................................
// NORMAL JUMPS & SUBROUTINE CALLS/RETURNS
// .................................................
uint8_t JMP_4C(uint8_t arg0, uint8_t arg1);    // JMP nnnn
uint8_t JMP_6C(uint8_t arg0, uint8_t arg1);    // JMP (nnnn)
uint8_t JSR_20(uint8_t arg0, uint8_t arg1);    // JSR nnnn
uint8_t RTI_40(uint8_t arg0, uint8_t arg1);    // RTI
uint8_t RTS_60(uint8_t arg0, uint8_t arg1);    // RTS

// .................................................
// CONDITIONAL BRANCHES
// .................................................
uint8_t BPL_10(uint8_t arg0, uint8_t arg1);    // N=0 plus/positive
uint8_t BMI_30(uint8_t arg0, uint8_t arg1);    // N=1 minus/negative/signed
uint8_t BVC_50(uint8_t arg0, uint8_t arg1);    // V=0 no overflow
uint8_t BVS_70(uint8_t arg0, uint8_t arg1);    // V=1 overflow
uint8_t BCC_90(uint8_t arg0, uint8_t arg1);    // C=0 less/below/no carry
uint8_t BCS_B0(uint8_t arg0, uint8_t arg1);    // C=1 above/greater/equal/carry
uint8_t BNE_D0(uint8_t arg0, uint8_t arg1);    // Z=0 not zero/not equal
uint8_t BEQ_F0(uint8_t arg0, uint8_t arg1);    // z=1 zero/equal

// .................................................
// INTERRUPTS, EXECPTIONS, BREAKPOINTS
// .................................................
uint8_t BRK_00(uint8_t arg0, uint8_t arg1);    // BRK

// .................................................
// CPU CONTROL
// .................................................
uint8_t CLC_18(uint8_t arg0, uint8_t arg1);    // Clear Carry Flag
uint8_t CLI_58(uint8_t arg0, uint8_t arg1);    // Clear interrupt disable bit
uint8_t CLD_D8(uint8_t arg0, uint8_t arg1);    // Clear decimal mode
uint8_t CLV_B8(uint8_t arg0, uint8_t arg1);    // Clear overflow flag
uint8_t SEC_38(uint8_t arg0, uint8_t arg1);    // Set carry flag
uint8_t SEI_78(uint8_t arg0, uint8_t arg1);    // Set interrupt disable bit
uint8_t SED_F8(uint8_t arg0, uint8_t arg1);    // Set decimal mode

// .................................................
// NO OPERATION
// .................................................
uint8_t NOP_EA(uint8_t arg0, uint8_t arg1);    // NOP

#endif
