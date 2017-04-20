#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#ifndef CPUROTSHIFT_H_
#define CPUROTSHIFT_H_


// .................................................
// SHIFT LEFT LOGICAL/ARITHMETIC
// .................................................
uint8_t ASL(uint8_t op, uint8_t arg0, uint8_t arg1);    // ASL A
                                                        // ASL nn
                                                        // ASL nn,X
                                                        // ASL nnnn
                                                        // ASL nnnn,X

// .................................................
// SHIFT RIGHT LOGICAL
// .................................................
uint8_t LSR(uint8_t op, uint8_t arg0, uint8_t arg1);    // LSR A
                                                        // LSR nn
                                                        // LSR nn,X
                                                        // LSR nnnn
                                                        // LSR nnnn,X

// .................................................
// ROTATE LEFT THROUGH CARRY
// .................................................
uint8_t ROL(uint8_t op, uint8_t arg0, uint8_t arg1);    // ROL A
                                                        // ROL nn
                                                        // ROL nn,X
                                                        // ROL nnnn
                                                        // ROL nnnn,X

// .................................................
// ROTATE RIGHT THROUGH CARRY
// .................................................
uint8_t ROR(uint8_t op, uint8_t arg0, uint8_t arg1);    // ROR A
                                                        // ROR nn
                                                        // ROR nn,X
                                                        // ROR nnnn
                                                        // ROR nnnn,X


#endif
