#ifndef CPUARITHLOGOPS_H_
#define CPUARITHLOGOPS_H_

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// .................................................
// ADD MEMORY TO ACCUMULATOR WITH CARRY
// .................................................
uint8_t ADC_69(uint8_t arg0, uint8_t arg1);    // ADC #nn
uint8_t ADC_65(uint8_t arg0, uint8_t arg1);    // ADC nn
uint8_t ADC_75(uint8_t arg0, uint8_t arg1);    // ADC nn,X
uint8_t ADC_6D(uint8_t arg0, uint8_t arg1);    // ADC nnnn
uint8_t ADC_7D(uint8_t arg0, uint8_t arg1);    // ADC nnnn,X
uint8_t ADC_79(uint8_t arg0, uint8_t arg1);    // ADC nnnn,Y
uint8_t ADC_61(uint8_t arg0, uint8_t arg1);    // ADC (nn,X)
uint8_t ADC_71(uint8_t arg0, uint8_t arg1);    // ADC (nn),Y

// .................................................
// SUBTRACT MEMORY FROM ACCUMULATOR WITH BORROW
// .................................................
uint8_t SBC_E9(uint8_t arg0, uint8_t arg1);    // SBC #nn
uint8_t SBC_E5(uint8_t arg0, uint8_t arg1);    // SBC nn
uint8_t SBC_F5(uint8_t arg0, uint8_t arg1);    // SBC nn,X
uint8_t SBC_ED(uint8_t arg0, uint8_t arg1);    // SBC nnnn
uint8_t SBC_FD(uint8_t arg0, uint8_t arg1);    // SBC nnnn,X
uint8_t SBC_F9(uint8_t arg0, uint8_t arg1);    // SBC nnnn,Y
uint8_t SBC_E1(uint8_t arg0, uint8_t arg1);    // SBC (nn,X)
uint8_t SBC_F1(uint8_t arg0, uint8_t arg1);    // SBC (nn),Y

// .................................................
// LOGICAL AND MEMORY WITH ACCUMULATOR
// .................................................
uint8_t AND_29(uint8_t arg0, uint8_t arg1);    // AND #nn
uint8_t AND_25(uint8_t arg0, uint8_t arg1);    // AND nn
uint8_t AND_35(uint8_t arg0, uint8_t arg1);    // AND nn,X
uint8_t AND_2D(uint8_t arg0, uint8_t arg1);    // AND nnnn
uint8_t AND_3D(uint8_t arg0, uint8_t arg1);    // AND nnnn,X
uint8_t AND_39(uint8_t arg0, uint8_t arg1);    // AND nnnn,Y
uint8_t AND_21(uint8_t arg0, uint8_t arg1);    // AND (nn,X)
uint8_t AND_31(uint8_t arg0, uint8_t arg1);    // AND (nn),Y

// .................................................
// EXCLUSIVE-OR MEMORY WITH ACCUMULATOR
// .................................................
uint8_t EOR_49(uint8_t arg0, uint8_t arg1);    // EOR #nn
uint8_t EOR_45(uint8_t arg0, uint8_t arg1);    // EOR nn
uint8_t EOR_55(uint8_t arg0, uint8_t arg1);    // EOR nn,X
uint8_t EOR_4D(uint8_t arg0, uint8_t arg1);    // EOR nnnn
uint8_t EOR_5D(uint8_t arg0, uint8_t arg1);    // EOR nnnn,X
uint8_t EOR_59(uint8_t arg0, uint8_t arg1);    // EOR nnnn,Y
uint8_t EOR_41(uint8_t arg0, uint8_t arg1);    // EOR (nn,X)
uint8_t EOR_51(uint8_t arg0, uint8_t arg1);    // EOR (nn),Y
                                                        
// .................................................
// LOGICAL OR MEMORY WITH ACCUMULATOR
// .................................................
uint8_t ORA_09(uint8_t arg0, uint8_t arg1);    // ORA #nn
uint8_t ORA_05(uint8_t arg0, uint8_t arg1);    // ORA nn
uint8_t ORA_15(uint8_t arg0, uint8_t arg1);    // ORA nn,X
uint8_t ORA_0D(uint8_t arg0, uint8_t arg1);    // ORA nnnn
uint8_t ORA_1D(uint8_t arg0, uint8_t arg1);    // ORA nnnn,X
uint8_t ORA_19(uint8_t arg0, uint8_t arg1);    // ORA nnnn,Y
uint8_t ORA_01(uint8_t arg0, uint8_t arg1);    // ORA (nn,X)
uint8_t ORA_11(uint8_t arg0, uint8_t arg1);    // ORA (nn),Y

// .................................................
// COMPARE
// .................................................
// Compare A with Memory or Immediate
uint8_t CMP_C9(uint8_t arg0, uint8_t arg1);    // CMP #nn
uint8_t CMP_C5(uint8_t arg0, uint8_t arg1);    // CMP nn
uint8_t CMP_D5(uint8_t arg0, uint8_t arg1);    // CMP nn,X
uint8_t CMP_CD(uint8_t arg0, uint8_t arg1);    // CMP nnnn
uint8_t CMP_DD(uint8_t arg0, uint8_t arg1);    // CMP nnnn,X
uint8_t CMP_D9(uint8_t arg0, uint8_t arg1);    // CMP nnnn,Y
uint8_t CMP_C1(uint8_t arg0, uint8_t arg1);    // CMP (nn,X)
uint8_t CMP_D1(uint8_t arg0, uint8_t arg1);    // CMP (nn),Y

// Compare X with Memory or Immediate
uint8_t CPX_E0(uint8_t arg0, uint8_t arg1);    // CPX #nn
uint8_t CPX_E4(uint8_t arg0, uint8_t arg1);    // CPX nn
uint8_t CPX_EC(uint8_t arg0, uint8_t arg1);    // CPX nnnn

// Compare Y with Memory or Immediate
uint8_t CPY_C0(uint8_t arg0, uint8_t arg1);    // CPY #nn
uint8_t CPY_C4(uint8_t arg0, uint8_t arg1);    // CPY nn
uint8_t CPY_CC(uint8_t arg0, uint8_t arg1);    // CPY nnnn

// .................................................
// BIT TEST
// .................................................
uint8_t BIT_24(uint8_t arg0, uint8_t arg1);    // BIT nn
uint8_t BIT_2C(uint8_t arg0, uint8_t arg1);    // BIT nnnn

// .................................................
// INCREMENT BY ONE
// .................................................
// Increment memory
uint8_t INC_E6(uint8_t arg0, uint8_t arg1);    // INC nn
uint8_t INC_F6(uint8_t arg0, uint8_t arg1);    // INC nn,X
uint8_t INC_EE(uint8_t arg0, uint8_t arg1);    // INC nnnn
uint8_t INC_FE(uint8_t arg0, uint8_t arg1);    // INC nnnn,X

// Increment X
uint8_t INX_E8(uint8_t arg0, uint8_t arg1);    // INX

// Increment Y
uint8_t INY_C8(uint8_t arg0, uint8_t arg1);    // INY

// .................................................
// DECREMENT BY ONE
// .................................................
// Decrement memory
uint8_t DEC_C6(uint8_t arg0, uint8_t arg1);    // DEC nn
uint8_t DEC_D6(uint8_t arg0, uint8_t arg1);    // DEC nn,X
uint8_t DEC_CE(uint8_t arg0, uint8_t arg1);    // DEC nnnn
uint8_t DEC_DE(uint8_t arg0, uint8_t arg1);    // DEC nnnn,X

// Decrement X
uint8_t DEX_CA(uint8_t arg0, uint8_t arg1);    // DEX

// Decrement Y
uint8_t DEY_88(uint8_t arg0, uint8_t arg1);    // DEY


#endif
