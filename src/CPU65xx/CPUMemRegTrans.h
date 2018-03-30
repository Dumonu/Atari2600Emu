#ifndef CPUMEMREGTRANS_H_
#define CPUMEMREGTRANS_H_

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// .................................................
// REGISTER TO REGISTER TRANSFER
// .................................................
// Transfer A to Y
uint8_t TAY_A8(uint8_t arg0, uint8_t arg1);    // TAY

// Transfer A to X
uint8_t TAX_AA(uint8_t arg0, uint8_t arg1);    // TAX

// Transfer S to X
uint8_t TSX_BA(uint8_t arg0, uint8_t arg1);    // TSX

// Transfer Y to A
uint8_t TYA_98(uint8_t arg0, uint8_t arg1);    // TYA

// Transfer X to A
uint8_t TXA_8A(uint8_t arg0, uint8_t arg1);    // TXA

// Transfer X to S
uint8_t TXS_9A(uint8_t arg0, uint8_t arg1);    // TXS

// .................................................
// LOAD REGISTER FROM MEMORY/IMMEDIATE
// .................................................
// Load value into A
uint8_t LDA_A9(uint8_t arg0, uint8_t arg1);    // LDA #nn
uint8_t LDA_A5(uint8_t arg0, uint8_t arg1);    // LDA nn
uint8_t LDA_B5(uint8_t arg0, uint8_t arg1);    // LDA nn,X
uint8_t LDA_AD(uint8_t arg0, uint8_t arg1);    // LDA nnnn
uint8_t LDA_BD(uint8_t arg0, uint8_t arg1);    // LDA nnnn,X
uint8_t LDA_B9(uint8_t arg0, uint8_t arg1);    // LDA nnnn,Y
uint8_t LDA_A1(uint8_t arg0, uint8_t arg1);    // LDA (nn,X)
uint8_t LDA_B1(uint8_t arg0, uint8_t arg1);    // LDA (nn),Y

// Load value into X
uint8_t LDX_A2(uint8_t arg0, uint8_t arg1);    // LDX #nn
uint8_t LDX_A6(uint8_t arg0, uint8_t arg1);    // LDX nn
uint8_t LDX_B6(uint8_t arg0, uint8_t arg1);    // LDX nn,Y
uint8_t LDX_AE(uint8_t arg0, uint8_t arg1);    // LDX nnnn
uint8_t LDX_BE(uint8_t arg0, uint8_t arg1);    // LDX nnnn,Y

// Load value into Y
uint8_t LDY_A0(uint8_t arg0, uint8_t arg1);    // LDY #nn
uint8_t LDY_A4(uint8_t arg0, uint8_t arg1);    // LDY nn
uint8_t LDY_B4(uint8_t arg0, uint8_t arg1);    // LDY nn,X
uint8_t LDY_AC(uint8_t arg0, uint8_t arg1);    // LDY nnnn
uint8_t LDY_BC(uint8_t arg0, uint8_t arg1);    // LDY nnnn,X


// .................................................
// STORE REGISTER IN MEMORY
// .................................................
// Store A in memory
uint8_t STA_85(uint8_t arg0, uint8_t arg1);    // STA nn
uint8_t STA_95(uint8_t arg0, uint8_t arg1);    // STA nn,X
uint8_t STA_8D(uint8_t arg0, uint8_t arg1);    // STA nnnn
uint8_t STA_9D(uint8_t arg0, uint8_t arg1);    // STA nnnn,X
uint8_t STA_99(uint8_t arg0, uint8_t arg1);    // STA nnnn,Y
uint8_t STA_81(uint8_t arg0, uint8_t arg1);    // STA (nn,X)
uint8_t STA_91(uint8_t arg0, uint8_t arg1);    // STA (nn),Y

// Store X in memory
uint8_t STX_86(uint8_t arg0, uint8_t arg1);    // STX nn
uint8_t STX_96(uint8_t arg0, uint8_t arg1);    // STX nn,Y
uint8_t STX_8E(uint8_t arg0, uint8_t arg1);    // STX nnnn

// Store Y in memory
uint8_t STY_84(uint8_t arg0, uint8_t arg1);    // STY nn
uint8_t STY_94(uint8_t arg0, uint8_t arg1);    // STY nn,X
uint8_t STY_8C(uint8_t arg0, uint8_t arg1);    // STY nnnn

// .................................................
// PUSH/PULL
// .................................................
// Push A
uint8_t PHA_48(uint8_t arg0, uint8_t arg1);    // PHA

// Push P
uint8_t PHP_08(uint8_t arg0, uint8_t arg1);    // PHP

// Pull A
uint8_t PLA_68(uint8_t arg0, uint8_t arg1);    // PLA

// Pull P
uint8_t PLP_28(uint8_t arg0, uint8_t arg1);    // PLP


#endif
