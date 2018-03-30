#ifndef CPUROTSHIFT_H_
#define CPUROTSHIFT_H_

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// .................................................
// SHIFT LEFT LOGICAL/ARITHMETIC
// .................................................
uint8_t ASL_0A(uint8_t arg0, uint8_t arg1);    // ASL A
uint8_t ASL_06(uint8_t arg0, uint8_t arg1);    // ASL nn
uint8_t ASL_16(uint8_t arg0, uint8_t arg1);    // ASL nn,X
uint8_t ASL_0E(uint8_t arg0, uint8_t arg1);    // ASL nnnn
uint8_t ASL_1E(uint8_t arg0, uint8_t arg1);    // ASL nnnn,X

// .................................................
// SHIFT RIGHT LOGICAL
// .................................................
uint8_t LSR_4A(uint8_t arg0, uint8_t arg1);    // LSR A
uint8_t LSR_46(uint8_t arg0, uint8_t arg1);    // LSR nn
uint8_t LSR_56(uint8_t arg0, uint8_t arg1);    // LSR nn,X
uint8_t LSR_4E(uint8_t arg0, uint8_t arg1);    // LSR nnnn
uint8_t LSR_5E(uint8_t arg0, uint8_t arg1);    // LSR nnnn,X

// .................................................
// ROTATE LEFT THROUGH CARRY
// .................................................
uint8_t ROL_2A(uint8_t arg0, uint8_t arg1);    // ROL A
uint8_t ROL_26(uint8_t arg0, uint8_t arg1);    // ROL nn
uint8_t ROL_36(uint8_t arg0, uint8_t arg1);    // ROL nn,X
uint8_t ROL_2E(uint8_t arg0, uint8_t arg1);    // ROL nnnn
uint8_t ROL_3E(uint8_t arg0, uint8_t arg1);    // ROL nnnn,X

// .................................................
// ROTATE RIGHT THROUGH CARRY
// .................................................
uint8_t ROR_6A(uint8_t arg0, uint8_t arg1);    // ROR A
uint8_t ROR_66(uint8_t arg0, uint8_t arg1);    // ROR nn
uint8_t ROR_76(uint8_t arg0, uint8_t arg1);    // ROR nn,X
uint8_t ROR_6E(uint8_t arg0, uint8_t arg1);    // ROR nnnn
uint8_t ROR_7E(uint8_t arg0, uint8_t arg1);    // ROR nnnn,X


#endif
