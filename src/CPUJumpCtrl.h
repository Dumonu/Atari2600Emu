#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#ifndef CPUJUMPCTRL_H_
#define CPUJUMPCTRL_H_

// .................................................
// NORMAL JUMPS & SUBROUTINE CALLS/RETURNS
// .................................................
uint8_t JMP(uint8_t op, uint8_t arg0, uint8_t arg1);    // JMP nnnn
                                                        // JMP (nnnn)
uint8_t JSR(uint8_t op, uint8_t arg0, uint8_t arg1);    // JSR nnnn
uint8_t RTI(uint8_t op, uint8_t arg0, uint8_t arg1);    // RTI
uint8_t RTS(uint8_t op, uint8_t arg0, uint8_t arg1);    // RTS

// .................................................
// CONDITIONAL BRANCHES
// .................................................
uint8_t BPL(uint8_t op, uint8_t arg0, uint8_t arg1);    // N=0 plus/positive
uint8_t BMI(uint8_t op, uint8_t arg0, uint8_t arg1);    // N=1 minus/negative/signed
uint8_t BVC(uint8_t op, uint8_t arg0, uint8_t arg1);    // V=0 no overflow
uint8_t BVS(uint8_t op, uint8_t arg0, uint8_t arg1);    // V=1 overflow
uint8_t BCC(uint8_t op, uint8_t arg0, uint8_t arg1);    // C=0 less/below/no carry
uint8_t BCS(uint8_t op, uint8_t arg0, uint8_t arg1);    // C=1 above/greater/equal/carry
uint8_t BNE(uint8_t op, uint8_t arg0, uint8_t arg1);    // Z=0 not zero/not equal
uint8_t BEQ(uint8_t op, uint8_t arg0, uint8_t arg1);    // z=1 zero/equal

// .................................................
// INTERRUPTS, EXECPTIONS, BREAKPOINTS
// .................................................
uint8_t BRK(uint8_t op, uint8_t arg0, uint8_t arg1);    // BRK

// .................................................
// CPU CONTROL
// .................................................
uint8_t CLC(uint8_t op, uint8_t arg0, uint8_t arg1);    // Clear Carry Flag
uint8_t CLI(uint8_t op, uint8_t arg0, uint8_t arg1);    // Clear interrupt disable bit
uint8_t CLD(uint8_t op, uint8_t arg0, uint8_t arg1);    // Clear decimal mode
uint8_t CLV(uint8_t op, uint8_t arg0, uint8_t arg1);    // Clear overflow flag
uint8_t SEC(uint8_t op, uint8_t arg0, uint8_t arg1);    // Set carry flag
uint8_t SEI(uint8_t op, uint8_t arg0, uint8_t arg1);    // Set interrupt disable bit
uint8_t SED(uint8_t op, uint8_t arg0, uint8_t arg1);    // Set decimal mode

// .................................................
// NO OPERATION
// .................................................
uint8_t NOP(uint8_t op, uint8_t arg0, uint8_t arg1);    // NOP

#endif
