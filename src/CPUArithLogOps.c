#include "a2600.h"

// .................................................
// ADD MEMORY TO ACCUMULATOR WITH CARRY
// .................................................
// NOTE: ADC and SBC are affected by D-flag
uint8_t ADC(uint8_t op, uint8_t arg0, uint8_t arg1)
{
    uint8_t addend = 0;

    // GET ADDEND HERE;
    uint16_t addr = 0;
    switch(op)
    {
    // 69 nn    nzc--v  2   ADC #nn     ADC A,nn        A=A+C+nn
    case 0x69:
        addend = arg0;
        tick(2);
        PC += 2;
        break;
    // 65 nn    nzc--v  3   ADC nn      ADC A,[nn]      A=A+C+[nn]
    case 0x65:
        addend = read(arg0);
        tick(3);
        PC += 2;
        break;
    // 75 nn    nzc--v  4   ADC nn,X    ADC A,[nn+X]    A=A+C+[nn+X]
    case 0x75:
        addend = read((uint8_t)(arg0 + X));
        tick(4);
        PC += 2;
        break; 
    // 6D nn nn nzc--v  4   ADC nnnn    ADC A,[nnnn]    A=A+C+[nnnn]
    case 0x6D:
        addend = read((((uint16_t)arg1) << 8) + arg0);
        tick(4);
        PC += 3;
        break;
    // 7D nn nn nzc--v  4*  ADC nnnn,X  ADC A,[nnnn+X]  A=A+C+[nnnn+X]
    case 0x7D:
        addr = (((uint16_t)arg1) << 8) + arg0 + X;
        addend = read(addr);
        tick((addr >> 8) > arg1 ? 5 : 4);
        PC += 3;
        break;
    // 79 nn nn nzc--v  4*  ADC nnnn,Y  ADC A,[nnnn+Y]  A=A+C+[nnnn+Y]
    case 0x79:
        addr = (((uint16_t)arg1) << 8) + arg0 + Y;
        addend = read(addr);
        tick((addr >> 8) > arg1 ? 5 : 4);
        PC += 3;
        break;
    // 61 nn    nzc--v  6   ADC (nn,X)  ADC A,[[nn+X]]  A=A+C+[word[nn+X]]
    case 0x61:
        addend = read(((uint16_t)(read(arg0 + X + 1)) << 8) + read(arg0 + X));
        tick(6);
        PC += 2;
        break;
    // 71 nn    nzc--v  5*  ADC (nn),Y  ADC A,[[nn]+Y]  A=A+C+[word[nn]+Y]
    case 0x71:
        addr = (uint16_t)(read(arg0 + 1) << 8) + read(arg0);
        addend = read(addr + Y);
        tick(((addr + Y) >> 8) > (addr >> 8) ? 6 : 5);
        PC += 2;
        break; 
    }

    P = P & 0b00111100;                         // zero-out the N,V,Z, and C flags

    //Deal with BCD mode here
    if(P & 0b00001000) // if D-flag is set
    {
        // A: Seq. 1
        // C: Seq. 1
        // N: Seq. 2
        // Z: bin

        // Seq. 1
        // 1a. AL = (A & 0x0F) + (B & 0x0F) + C
        // 1b. If AL >= 0x0A, then AL = ((AL + 0x06) & 0x0F) + 0x10
        // 1c. A = (A & 0xF0) + (B & 0xF0) + AL
        // 1d. Note that A can be >= 0x100 at this point
        // 1e. If (A >= 0xA0), then A = A + 0x60
        // 1f. The accumulator result is the lower 8  bits of A
        // 1g. The carry result is 1 if A >= 0x100, and is 0 if A < 0x100

        // Seq. 2
        // 2a. AL = (A & 0x0F) + (B & 0x0F) + C
        // 2b. If AL >= 0x0A, then AL = ((AL + 0x06) & 0x0F) + 0x10
        // 2c. A = (A & 0xF0) + (B & 0xF0) + AL, using signed arithmetic
        // 2d. The N flag result is 1 if bit 7 of A is 1, and is 0 if bit 7 of A is 0
        // 2e. The V flag result is 1 if A < -128 or A > 127, and is 0 if -128 <= A <= 127

        uint16_t AL = (A & 0x0F) + (addend & 0x0F) + (P & 0x01);
        if(AL >= 0x0A)
            AL = ((AL + 0x06) & 0x0F) + 0x10;
        uint16_t temp = (A & 0xF0) + (addend & 0xF0) + AL;
        int16_t sTemp = (int8_t)(A & 0xF0) + (int8_t)(addend & 0xF0) + (int16_t)AL;
        P = P | (temp & 0b10000000);    // Negative/Sign Flag
        P = P | (sTemp < -128 || sTemp > 127 ? 0b01000000 : 0x00); // Overflow flag
        if(temp >= 0xA0)
            temp = temp + 0x60;
        A = (uint8_t)temp;
        P = P | ((A + addend + (P & 0x01)) != 0 ? 0x00 : 0x02); // Zero Flag
        P = P | (temp >= 0x100 ? 0x01 : 0x00);  //Carry Flag

    }
    else
    {
        uint16_t temp = A + addend + (P & 0x01);    //A=A+addend+carry
        int16_t sTemp = (int8_t)A + (int8_t)addend + (P & 0x01);
        A = (uint8_t)temp;
        P = P | (A & 0b10000000);                                   // Negative/Sign Flag
        P = P | (sTemp < -128 || sTemp > 127 ? 0b01000000 : 0x00);  // Overflow Flag
        P = P | (A != 0 ? 0x00 : 0x02);                             //Zero Flag
        P = P | (temp >= 0x100 ? 0x01 : 0x00);                      //Carry Flag
    }
	return 1;
}    

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
