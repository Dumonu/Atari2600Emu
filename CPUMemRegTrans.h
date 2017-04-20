#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#ifndef CPUMEMREGTRANS_H_
#define CPUMEMREGTRANS_H_

// .................................................
// REGISTER/IMMEDITATE TO REGISTER TRANSFER
// .................................................
uint8_t TAY(uint8_t op, uint8_t arg0, uint8_t arg1);    // TAY
uint8_t TAX(uint8_t op, uint8_t arg0, uint8_t arg1);    // TAX
uint8_t TSX(uint8_t op, uint8_t arg0, uint8_t arg1);    // TSX
uint8_t TYA(uint8_t op, uint8_t arg0, uint8_t arg1);    // TYA
uint8_t TXA(uint8_t op, uint8_t arg0, uint8_t arg1);    // TXA
uint8_t TXS(uint8_t op, uint8_t arg0, uint8_t arg1);    // TXS
                                                        // LDA #nn
                                                        // LDX #nn
                                                        // LDY #nn

// .................................................
// LOAD REGISTER FROM MEMORY
// .................................................
uint8_t LDA(uint8_t op, uint8_t arg0, uint8_t arg1);    // LDA nn
                                                        // LDA nn,X
                                                        // LDA nnnn
                                                        // LDA nnnn,X
                                                        // LDA nnnn,Y
                                                        // LDA (nn,X)
                                                        // LDA (nn),Y
uint8_t LDX(uint8_t op, uint8_t arg0, uint8_t arg1);    // LDX nn
                                                        // LDX nn,Y
                                                        // LDX nnnn
                                                        // LDX nnnn,Y
uint8_t LDY(uint8_t op, uint8_t arg0, uint8_t arg1);    // LDY nn
                                                        // LDY nn,X
                                                        // LDY nnnn
                                                        // LDY nnnn,X


// .................................................
// STORE REGISTER IN MEMORY
// .................................................
uint8_t STA(uint8_t op, uint8_t arg0, uint8_t arg1);    // STA nn
                                                        // STA nn,X
                                                        // STA nnnn
                                                        // STA nnnn,X
                                                        // STA nnnn,Y
                                                        // STA (nn,X)
                                                        // STA (nn),Y
uint8_t STY(uint8_t op, uint8_t arg0, uint8_t arg1);    // STX nn
                                                        // STX nn,Y
                                                        // STX nn,Y
                                                        // STX nnnn
uint8_t STX(uint8_t op, uint8_t arg0, uint8_t arg1);    // STY nn
                                                        // STY nn,X
                                                        // STY nnnn

// .................................................
// PUSH/PULL
// .................................................
uint8_t PHA(uint8_t op, uint8_t arg0, uint8_t arg1);    // PHA
uint8_t PHP(uint8_t op, uint8_t arg0, uint8_t arg1);    // PHP
uint8_t PLA(uint8_t op, uint8_t arg0, uint8_t arg1);    // PLA
uint8_t PLP(uint8_t op, uint8_t arg0, uint8_t arg1);    // PLP


#endif
