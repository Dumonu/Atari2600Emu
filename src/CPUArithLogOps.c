#include "a2600.h"

// .................................................
// ADD MEMORY TO ACCUMULATOR WITH CARRY
// .................................................
// NOTE: ADC and SBC are affected by D-flag
uint8_t ADC(uint8_t op, uint8_t arg0, uint8_t arg1)
{
    uint8_t addend = 0;

    // GET ADDEND HERE;

    uint8_t 
    uint16_t temp = A + addend + (P & 0x01);    //A=A+addend+carry
    A = (uint8_t)temp;
    P = P & 0b00111100;                         // zero-out the N,V,Z, and C flags
    P = P | (A & 0b10000000);                   // Negative/Sign Flag
    P = P | 0b0;                                // Overflow Flag TODO
    P = P | (A != 0 ? 0x00 : 0x02);             //Zero Flag
    P = P | (temp > (uint16_t)A ? 0x01 : 0x00); //Carry Flag


	return 0;
}    // ADC #nn
                                                        // ADC nn
                                                        // ADC nn,X
                                                        // ADC nnnn
                                                        // ADC nnnn,X
                                                        // ADC nnnn,Y
                                                        // ADC (nn,X)
                                                        // ADC (nn),Y

// .................................................
// SUBTRACT MEMORY FROM ACCUMULATOR WITH BORROW
// .................................................
uint8_t SBC(uint8_t op, uint8_t arg0, uint8_t arg1)
{
	return 1;
}    // SBC #nn
                                                        // SBC nn
                                                        // SBC nn,X
                                                        // SBC nnnn
                                                        // SBC nnnn,X
                                                        // SBC nnnn,Y
                                                        // SBC (nn,X)
                                                        // SBC (nn),Y

// .................................................
// LOGICAL AND MEMORY WITH ACCUMULATOR
// .................................................
uint8_t AND(uint8_t op, uint8_t arg0, uint8_t arg1)
{
	return 1;
}    // AND #nn
                                                        // AND nn
                                                        // AND nn,X
                                                        // AND nnnn
                                                        // AND nnnn,X
                                                        // AND nnnn,Y
                                                        // AND (nn,X)
                                                        // AND (nn),Y

// .................................................
// EXCLUSIVE-OR MEMORY WITH ACCUMULATOR
// .................................................
uint8_t EOR(uint8_t op, uint8_t arg0, uint8_t arg1)
{
	return 1;
}    // EOR #nn
                                                        // EOR nn
                                                        // EOR nn,X
                                                        // EOR nnnn
                                                        // EOR nnnn,X
                                                        // EOR nnnn,Y
                                                        // EOR (nn,X)
                                                        // EOR (nn),Y
                                                        
// .................................................
// LOGICAL OR MEMORY WITH ACCUMULATOR
// .................................................
uint8_t ORA(uint8_t op, uint8_t arg0, uint8_t arg1)
{
	return 1;
}    // ORA #nn
                                                        // ORA nn
                                                        // ORA nn,X
                                                        // ORA nnnn
                                                        // ORA nnnn,X
                                                        // ORA nnnn,Y
                                                        // ORA (nn,X)
                                                        // ORA (nn),Y

// .................................................
// COMPARE
// .................................................
uint8_t CMP(uint8_t op, uint8_t arg0, uint8_t arg1)
{
	return 1;
}    // CMP #nn
                                                        // CMP nn
                                                        // CMP nn,X
                                                        // CMP nnnn
                                                        // CMP nnnn,X
                                                        // CMP nnnn,Y
                                                        // CMP (nn,X)
                                                        // CMP (nn),Y
uint8_t CPX(uint8_t op, uint8_t arg0, uint8_t arg1)
{
	return 1;
}    // CPX #nn
                                                        // CPX nn
                                                        // CPX nnnn
uint8_t CPY(uint8_t op, uint8_t arg0, uint8_t arg1)
{
	return 1;
}    // CPY #nn
                                                        // CPY nn
                                                        // CPY nnnn

// .................................................
// BIT TEST
// .................................................
uint8_t BIT(uint8_t op, uint8_t arg0, uint8_t arg1)
{
	return 1;
}    // BIT nn
                                                        // BIT nnnn

// .................................................
// INCREMENT BY ONE
// .................................................
uint8_t INC(uint8_t op, uint8_t arg0, uint8_t arg1)
{
	return 1;
}    // INC nn
                                                        // INC nn,X
                                                        // INC nnnn
                                                        // INC nnnn,X
uint8_t INX(uint8_t op, uint8_t arg0, uint8_t arg1)
{
	return 1;
}    // INX
uint8_t INY(uint8_t op, uint8_t arg0, uint8_t arg1)
{
	return 1;
}    // INY

// .................................................
// DECREMENT BY ONE
// .................................................
uint8_t DEC(uint8_t op, uint8_t arg0, uint8_t arg1)
{
	return 1;
}    // DEC nn
                                                        // DEC nn,X
                                                        // DEC nnnn
                                                        // DEC nnnn,X
uint8_t DEX(uint8_t op, uint8_t arg0, uint8_t arg1)
{
	return 1;
}    // DEX
uint8_t DEY(uint8_t op, uint8_t arg0, uint8_t arg1)
{
	return 1;
}    // DEY
