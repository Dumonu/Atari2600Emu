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
        if(addr >> 8 > arg1)
        {
            read(addr - 0x0100); //Dummy read cycle; bug in CPU
            tick(1);
        }
        addend = read(addr);
        tick(4);
        PC += 3;
        break;
    // 79 nn nn nzc--v  4*  ADC nnnn,Y  ADC A,[nnnn+Y]  A=A+C+[nnnn+Y]
    case 0x79:
        addr = (((uint16_t)arg1) << 8) + arg0 + Y;
        if(addr >> 8 > arg1)
        {
            read(addr - 0x0100); //Dummy read cycle; bug in CPU
            tick(1);
        }
        addend = read(addr);
        tick(4);
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
        if((addr + Y) >> 8 > arg1)
        {
            read((addr + Y) - 0x0100); //Dummy read cycle; bug in CPU
            tick(1);
        }
        addend = read(addr + Y);
        tick(5);
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
	return 0;
}    

// .................................................
// SUBTRACT MEMORY FROM ACCUMULATOR WITH BORROW
// .................................................
uint8_t SBC(uint8_t op, uint8_t arg0, uint8_t arg1)
{
    uint8_t subtrahend = 0;

    // GET SUBTRAHEND HERE;
    uint16_t addr = 0;
    switch(op)
    {
    // E9 nn    nzc--v  2   SBC #nn     SBC A,nn        A=A+C+nn
    case 0xE9:
        subtrahend = arg0;
        tick(2);
        PC += 2;
        break;
    // E5 nn    nzc--v  3   SBC nn      SBC A,[nn]      A=A+C+[nn]
    case 0xE5:
        subtrahend = read(arg0);
        tick(3);
        PC += 2;
        break;
    // F5 nn    nzc--v  4   SBC nn,X    SBC A,[nn+X]    A=A+C+[nn+X]
    case 0xF5:
        subtrahend = read((uint8_t)(arg0 + X));
        tick(4);
        PC += 2;
        break; 
    // ED nn nn nzc--v  4   SBC nnnn    SBC A,[nnnn]    A=A+C+[nnnn]
    case 0xED:
        subtrahend = read((((uint16_t)arg1) << 8) + arg0);
        tick(4);
        PC += 3;
        break;
    // FD nn nn nzc--v  4*  SBC nnnn,X  SBC A,[nnnn+X]  A=A+C+[nnnn+X]
    case 0xFD:
        addr = (((uint16_t)arg1) << 8) + arg0 + X;
        if(addr >> 8 > arg1)
        {
            read(addr - 0x0100); //Dummy read cycle; bug in CPU
            tick(1);
        }
        subtrahend = read(addr);
        tick(4);
        PC += 3;
        break;
    // F9 nn nn nzc--v  4*  SBC nnnn,Y  SBC A,[nnnn+Y]  A=A+C+[nnnn+Y]
    case 0xF9:
        addr = (((uint16_t)arg1) << 8) + arg0 + Y;
        if(addr >> 8 > arg1)
        {
            read(addr - 0x0100); //Dummy read cycle; bug in CPU
            tick(1);
        }
        subtrahend = read(addr);
        tick(4);
        PC += 3;
        break;
    // E1 nn    nzc--v  6   SBC (nn,X)  SBC A,[[nn+X]]  A=A+C+[word[nn+X]]
    case 0xE1:
        subtrahend = read(((uint16_t)(read(arg0 + X + 1)) << 8) + read(arg0 + X));
        tick(6);
        PC += 2;
        break;
    // F1 nn    nzc--v  5*  SBC (nn),Y  SBC A,[[nn]+Y]  A=A+C+[word[nn]+Y]
    case 0xF1:
        addr = (uint16_t)(read(arg0 + 1) << 8) + read(arg0);
        if((addr + Y) >> 8 > arg1)
        {
            read((addr + Y) - 0x0100); //Dummy read cycle; bug in CPU
            tick(1);
        }
        subtrahend = read(addr + Y);
        tick(5);
        PC += 2;
        break; 
    }

    P = P & 0b00111100;                         // zero-out the N,V,Z, and C flags
    uint16_t temp = A - subtrahend + (P & 0x01) - 1;
    int16_t sTemp = (int8_t)A - (int8_t)subtrahend + (P & 0x01) - 1;
    P = P | (temp & 0b10000000);                                   // Negative/Sign Flag
    P = P | (sTemp < -128 || sTemp > 127 ? 0b01000000 : 0x00);  // Overflow Flag
    P = P | (temp != 0 ? 0x00 : 0x02);                             //Zero Flag
    P = P | (sTemp < 0 ? 0x01 : 0x00);                      //Carry Flag

    //Deal with BCD mode here
    if(P & 0b00001000) // if D-flag is set
    {
        // A: Seq. 3
        // C: bin
        // N: bin
        // V: bin
        // Z: bin

        // Seq. 3:
        // 3a. AL = (A & 0x0F) - (B & 0x0F) + C - 1
        // 3b. If AL < 0, then AL = ((AL - 0x06) & 0x0F) - 0x10
        // 3c. A = (A & 0xF0) - (B & 0xF0) + AL
        // 3d. If A < 0, then A = A - 0x60
        // 3e. The accumulator result is the lower 8 bits of A

        uint16_t AL = (A & 0x0F) - (subtrahend & 0x0F) + (P & 0x01) - 1;
        if(AL & 0x8000) // if (AL < 0)
            AL = ((AL - 0x06) & 0x0F) - 0x10;
        temp = (A & 0xF0) - (subtrahend & 0xF0) + AL;
        if(temp & 0x8000) // if (temp < 0)
            temp = temp - 0x60;
    }
    A = (uint8_t)temp;
	return 0;
}    

// .................................................
// LOGICAL AND MEMORY WITH ACCUMULATOR
// .................................................
uint8_t AND(uint8_t op, uint8_t arg0, uint8_t arg1)
{
    uint8_t conjunct = 0;

    // GET CONJUNCT HERE
    uint16_t addr = 0;
    switch(op)
    {
    // 29 nn    nz----  2   AND #nn     AND A,nn        A=A AND nn
    case 0x29:
        conjunct = arg0;
        tick(2);
        PC += 2;
        break;
    // 25 nn    nz----  3   AND nn      AND A,[nn]      A=A AND [nn]
    case 0x25:
        conjunct = read(arg0);
        tick(3);
        PC += 2;
        break;
    // 35 nn    nz----  4   AND nn,X    AND A,[nn+X]    A=A AND [nn+X]
    case 0x35:
        conjunct = read((uint8_t)(arg0 + X));
        tick(4);
        PC += 2;
        break; 
    // 2D nn nn nz----  4   AND nnnn    AND A,[nnnn]    A=A AND [nnnn]
    case 0x2D:
        conjunct = read((((uint16_t)arg1) << 8) + arg0);
        tick(4);
        PC += 3;
        break;
    // 3D nn nn nz----  4*  AND nnnn,X  AND A,[nnnn+X]  A=A AND [nnnn+X]
    case 0x3D:
        addr = (((uint16_t)arg1) << 8) + arg0 + X;
        if(addr >> 8 > arg1)
        {
            read(addr - 0x0100); //Dummy read cycle; bug in CPU
            tick(1);
        }
        conjunct = read(addr);
        tick(4);
        PC += 3;
        break;
    // 39 nn nn nz----  4*  AND nnnn,Y  AND A,[nnnn+Y]  A=A AND [nnnn+Y]
    case 0x39:
        addr = (((uint16_t)arg1) << 8) + arg0 + Y;
        if(addr >> 8 > arg1)
        {
            read(addr - 0x0100); //Dummy read cycle; bug in CPU
            tick(1);
        }
        conjunct = read(addr);
        tick(4);
        PC += 3;
        break;
    // 21 nn    nz----  6   AND (nn,X)  AND A,[[nn+X]]  A=A AND [word[nn+X]]
    case 0x21:
        conjunct = read(((uint16_t)(read(arg0 + X + 1)) << 8) + read(arg0 + X));
        tick(6);
        PC += 2;
        break;
    // 31 nn    nz----  5*  AND (nn),Y  AND A,[[nn]+Y]  A=A AND [word[nn]+Y]
    case 0x31:
        addr = (uint16_t)(read(arg0 + 1) << 8) + read(arg0);
        if((addr + Y) >> 8 > arg1)
        {
            read((addr + Y) - 0x0100); //Dummy read cycle; bug in CPU
            tick(1);
        }
        conjunct = read(addr + Y);
        tick(5);
        PC += 2;
        break; 
    }
    
    A = A & conjunct;
    P = P & 0b01111101; // We're setting the N-flag and the Z-flag
    P = P | (A & 0x80); // N-flag is same as leading bit of A
    P = P | (A != 0 ? 0x00 : 0x02); // Z-flag is set when A is 0

	return 0;
}

// .................................................
// EXCLUSIVE-OR MEMORY WITH ACCUMULATOR
// .................................................
uint8_t EOR(uint8_t op, uint8_t arg0, uint8_t arg1)
{
    uint8_t disjunct = 0;

    // GET DISJUNCT HERE
    uint16_t addr = 0;
    switch(op)
    {
    // 49 nn    nz----  2   EOR #nn     XOR A,nn        A=A XOR nn
    case 0x49:
        disjunct = arg0;
        tick(2);
        PC += 2;
        break;
    // 45 nn    nz----  3   EOR nn      XOR A,[nn]      A=A XOR [nn]
    case 0x45:
        disjunct = read(arg0);
        tick(3);
        PC += 2;
        break;
    // 55 nn    nz----  4   EOR nn,X    XOR A,[nn+X]    A=A XOR [nn+X]
    case 0x55:
        disjunct = read((uint8_t)(arg0 + X));
        tick(4);
        PC += 2;
        break; 
    // 4D nn nn nz----  4   EOR nnnn    XOR A,[nnnn]    A=A XOR [nnnn]
    case 0x4D:
        disjunct = read((((uint16_t)arg1) << 8) + arg0);
        tick(4);
        PC += 3;
        break;
    // 5D nn nn nz----  4*  EOR nnnn,X  XOR A,[nnnn+X]  A=A XOR [nnnn+X]
    case 0x5D:
        addr = (((uint16_t)arg1) << 8) + arg0 + X;
        if(addr >> 8 > arg1)
        {
            read(addr - 0x0100); //Dummy read cycle; bug in CPU
            tick(1);
        }
        disjunct = read(addr);
        tick(4);
        PC += 3;
        break;
    // 59 nn nn nz----  4*  EOR nnnn,Y  XOR A,[nnnn+Y]  A=A XOR [nnnn+Y]
    case 0x59:
        addr = (((uint16_t)arg1) << 8) + arg0 + Y;
        if(addr >> 8 > arg1)
        {
            read(addr - 0x0100); //Dummy read cycle; bug in CPU
            tick(1);
        }
        disjunct = read(addr);
        tick(4);
        PC += 3;
        break;
    // 41 nn    nz----  6   EOR (nn,X)  XOR A,[[nn+X]]  A=A XOR [word[nn+X]]
    case 0x41:
        disjunct = read(((uint16_t)(read(arg0 + X + 1)) << 8) + read(arg0 + X));
        tick(6);
        PC += 2;
        break;
    // 51 nn    nz----  5*  EOR (nn),Y  XOR A,[[nn]+Y]  A=A XOR [word[nn]+Y]
    case 0x51:
        addr = (uint16_t)(read(arg0 + 1) << 8) + read(arg0);
        if((addr + Y) >> 8 > arg1)
        {
            read((addr + Y) - 0x0100); //Dummy read cycle; bug in CPU
            tick(1);
        }
        disjunct = read(addr + Y);
        tick(5);
        PC += 2;
        break; 
    }
    
    A = A ^ disjunct;
    P = P & 0b01111101; // We're setting the N-flag and the Z-flag
    P = P | (A & 0x80); // N-flag is same as leading bit of A
    P = P | (A != 0 ? 0x00 : 0x02); // Z-flag is set when A is 0

	return 0;
}    
                                                        
// .................................................
// LOGICAL OR MEMORY WITH ACCUMULATOR
// .................................................
uint8_t ORA(uint8_t op, uint8_t arg0, uint8_t arg1)
{
    uint8_t disjunct = 0;

    // GET DISJUNCT HERE
    uint16_t addr = 0;
    switch(op)
    {
    // 09 nn    nz----  2   OR #nn     OR A,nn        A=A OR nn
    case 0x09:
        disjunct = arg0;
        tick(2);
        PC += 2;
        break;
    // 05 nn    nz----  3   OR nn      OR A,[nn]      A=A OR [nn]
    case 0x05:
        disjunct = read(arg0);
        tick(3);
        PC += 2;
        break;
    // 15 nn    nz----  4   OR nn,X    OR A,[nn+X]    A=A OR [nn+X]
    case 0x15:
        disjunct = read((uint8_t)(arg0 + X));
        tick(4);
        PC += 2;
        break; 
    // 0D nn nn nz----  4   OR nnnn    OR A,[nnnn]    A=A OR [nnnn]
    case 0x0D:
        disjunct = read((((uint16_t)arg1) << 8) + arg0);
        tick(4);
        PC += 3;
        break;
    // 1D nn nn nz----  4*  OR nnnn,X  OR A,[nnnn+X]  A=A OR [nnnn+X]
    case 0x1D:
        addr = (((uint16_t)arg1) << 8) + arg0 + X;
        if(addr >> 8 > arg1)
        {
            read(addr - 0x0100); //Dummy read cycle; bug in CPU
            tick(1);
        }
        disjunct = read(addr);
        tick(4);
        PC += 3;
        break;
    // 19 nn nn nz----  4*  OR nnnn,Y  OR A,[nnnn+Y]  A=A OR [nnnn+Y]
    case 0x19:
        addr = (((uint16_t)arg1) << 8) + arg0 + Y;
        if(addr >> 8 > arg1)
        {
            read(addr - 0x0100); //Dummy read cycle; bug in CPU
            tick(1);
        }
        disjunct = read(addr);
        tick(4);
        PC += 3;
        break;
    // 01 nn    nz----  6   OR (nn,X)  OR A,[[nn+X]]  A=A OR [word[nn+X]]
    case 0x01:
        disjunct = read(((uint16_t)(read(arg0 + X + 1)) << 8) + read(arg0 + X));
        tick(6);
        PC += 2;
        break;
    // 11 nn    nz----  5*  OR (nn),Y  OR A,[[nn]+Y]  A=A OR [word[nn]+Y]
    case 0x11:
        addr = (uint16_t)(read(arg0 + 1) << 8) + read(arg0);
        if((addr + Y) >> 8 > arg1)
        {
            read((addr + Y) - 0x0100); //Dummy read cycle; bug in CPU
            tick(1);
        }
        disjunct = read(addr + Y);
        tick(5);
        PC += 2;
        break; 
    }
    
    A = A | disjunct;
    P = P & 0b01111101; // We're setting the N-flag and the Z-flag
    P = P | (A & 0x80); // N-flag is same as leading bit of A
    P = P | (A != 0 ? 0x00 : 0x02); // Z-flag is set when A is 0

	return 0;
}    

// .................................................
// COMPARE
// .................................................
uint8_t CMP(uint8_t op, uint8_t arg0, uint8_t arg1)
{
    uint8_t subtrahend = 0;

    // GET SUBTRAHEND HERE;
    uint16_t addr = 0;
    switch(op)
    {
    // C9 nn    nzc---  2   CMP #nn     CMP A,nn        A-nn
    case 0xC9:
        subtrahend = arg0;
        tick(2);
        PC += 2;
        break;
    // C5 nn    nzc---  3   CMP nn      CMP A,[nn]      A-[nn]
    case 0xC5:
        subtrahend = read(arg0);
        tick(3);
        PC += 2;
        break;
    // D5 nn    nzc---  4   CMP nn,X    CMP A,[nn+X]    A-[nn+X]
    case 0xD5:
        subtrahend = read((uint8_t)(arg0 + X));
        tick(4);
        PC += 2;
        break; 
    // CD nn nn nzc---  4   CMP nnnn    CMP A,[nnnn]    A-[nnnn]
    case 0xCD:
        subtrahend = read((((uint16_t)arg1) << 8) + arg0);
        tick(4);
        PC += 3;
        break;
    // DD nn nn nzc---  4*  CMP nnnn,X  CMP A,[nnnn+X]  A-[nnnn+X]
    case 0xDD:
        addr = (((uint16_t)arg1) << 8) + arg0 + X;
        if(addr >> 8 > arg1)
        {
            read(addr - 0x0100); //Dummy read cycle; bug in CPU
            tick(1);
        }
        subtrahend = read(addr);
        tick(4);
        PC += 3;
        break;
    // D9 nn nn nzc---  4*  CMP nnnn,Y  CMP A,[nnnn+Y]  A-[nnnn+Y]
    case 0xD9:
        addr = (((uint16_t)arg1) << 8) + arg0 + Y;
        if(addr >> 8 > arg1)
        {
            read(addr - 0x0100); //Dummy read cycle; bug in CPU
            tick(1);
        }
        subtrahend = read(addr);
        tick(4);
        PC += 3;
        break;
    // C1 nn    nzc---  6   CMP (nn,X)  CMP A,[[nn+X]]  A-[word[nn+X]]
    case 0xC1:
        subtrahend = read(((uint16_t)(read(arg0 + X + 1)) << 8) + read(arg0 + X));
        tick(6);
        PC += 2;
        break;
    // D1 nn    nzc---  5*  CMP (nn),Y  CMP A,[[nn]+Y]  A-[word[nn]+Y]
    case 0xD1:
        addr = (uint16_t)(read(arg0 + 1) << 8) + read(arg0);
        if((addr + Y) >> 8 > arg1)
        {
            read((addr + Y) - 0x0100); //Dummy read cycle; bug in CPU
            tick(1);
        }
        subtrahend = read(addr + Y);
        tick(5);
        PC += 2;
        break; 
    }

    P = P & 0b01111100;                         // zero-out the N,Z, and C flags
    uint16_t temp = A - subtrahend;
    int16_t sTemp = (int8_t)A - (int8_t)subtrahend;
    P = P | (temp & 0b10000000);                                   // Negative/Sign Flag
    P = P | (temp != 0 ? 0x00 : 0x02);                             //Zero Flag
    P = P | (sTemp < 0 ? 0x01 : 0x00);                      //Carry Flag

	return 0;
}    

uint8_t CPX(uint8_t op, uint8_t arg0, uint8_t arg1)
{
    uint8_t subtrahend = 0;

    // GET SUBTRAHEND HERE;
    uint16_t addr = 0;
    switch(op)
    {
    // E0 nn    nzc---  2   CPX #nn     CMP X,nn        X-nn
    case 0xE0:
        subtrahend = arg0;
        tick(2);
        PC += 2;
        break;
    // E4 nn    nzc---  3   CPX nn      CMP X,[nn]      X-[nn]
    case 0xE4:
        subtrahend = read(arg0);
        tick(3);
        PC += 2;
        break;
    // EC nn nn nzc---  4   CPX nnnn    CMP X,[nnnn]    X-[nnnn]
    case 0xEC:
        subtrahend = read((((uint16_t)arg1) << 8) + arg0);
        tick(4);
        PC += 3;
        break;
    }

    P = P & 0b01111100;                         // zero-out the N,Z, and C flags
    uint16_t temp = X - subtrahend;
    int16_t sTemp = (int8_t)X - (int8_t)subtrahend;
    P = P | (temp & 0b10000000);                                   // Negative/Sign Flag
    P = P | (temp != 0 ? 0x00 : 0x02);                             //Zero Flag
    P = P | (sTemp < 0 ? 0x01 : 0x00);                      //Carry Flag

	return 0;
}   

uint8_t CPY(uint8_t op, uint8_t arg0, uint8_t arg1)
{
    uint8_t subtrahend = 0;

    // GET SUBTRAHEND HERE;
    uint16_t addr = 0;
    switch(op)
    {
    // C0 nn    nzc---  2   CPY #nn     CMP Y,nn        Y-nn
    case 0xC0:
        subtrahend = arg0;
        tick(2);
        PC += 2;
        break;
    // C4 nn    nzc---  3   CPY nn      CMP Y,[nn]      Y-[nn]
    case 0xC4:
        subtrahend = read(arg0);
        tick(3);
        PC += 2;
        break;
    // CC nn nn nzc---  4   CPX nnnn    CMP X,[nnnn]    X-[nnnn]
    case 0xCC:
        subtrahend = read((((uint16_t)arg1) << 8) + arg0);
        tick(4);
        PC += 3;
        break;
    }

    P = P & 0b01111100;                         // zero-out the N,Z, and C flags
    uint16_t temp = Y - subtrahend;
    int16_t sTemp = (int8_t)Y - (int8_t)subtrahend;
    P = P | (temp & 0b10000000);                                   // Negative/Sign Flag
    P = P | (temp != 0 ? 0x00 : 0x02);                             //Zero Flag
    P = P | (sTemp < 0 ? 0x01 : 0x00);                      //Carry Flag

	return 0;
}    

// .................................................
// BIT TEST
// .................................................
uint8_t BIT(uint8_t op, uint8_t arg0, uint8_t arg1)
{
    uint8_t testee;
    // 24 nn    xz---x  3   BIT nn      TEST A,[nn]     Test and set flags
    if(op == 0x24)
    {
        testee = read(arg0);
        tick(3);
        PC += 2;
    }
    // 2C nn nn xz---x  4   BIT nnnn    TEST A,[nnnn]   Test and set flags
    else
    {
        testee = read((((uint16_t)arg1) << 8) + arg0);
        tick(4);
        PC += 3;
    }
    P = P & 0b00111101;
    P = P | (((A & testee) == 0) ? 0x02 : 0x00);
    P = P | (testee & 0xC0);

	return 0;
}

// .................................................
// INCREMENT BY ONE
// .................................................
uint8_t INC(uint8_t op, uint8_t arg0, uint8_t arg1)
{ 
    uint16_t addr;
    switch(op)
    {
    // E6 nn    nz----  5   INC nn      INC [nn]        [nn]=[nn]+1
    case 0xE6:
        addr = (uint16_t)arg0;
        PC += 2;
        tick(5);
        break;
    // F6 nn    nz----  6   INC nn,X    INC [nn+X]      [nn+X]=[nn+X]+1
    case 0xF6:
        addr = (uint16_t)(arg0 + X);
        PC += 2;
        tick(6);
        break;
    // EE nn nn nz----  6   INC nnnn    INC [nnnn]      [nnnn]=[nnnn]+1
    case 0xEE:
        addr = (((uint16_t)arg1) << 8) + arg0;
        PC += 3;
        tick(6);
        break;
    // FE nn nn nz----  7   INC nnnn,X  INC [nnnn+X]    [nnnn+X]=[nnnn+X]+1
    case 0xFE:
        addr = (((uint16_t)arg1) << 8) + arg0 + X;
        PC += 3;
        tick(7);
        break;
    }
    uint8_t value = read(addr);
    write(addr, ++value);
    P = P & 0b01111101;
    P = P | (value & 0x80);
    P = P | ((value == 0) ? 0x02 : 0x00);

    return 0;
}

// E8       nz----  2   INX     INC X       X=X+1
uint8_t INX(uint8_t op, uint8_t arg0, uint8_t arg1)
{
    X++;
    PC++;
    tick(2);
    P = P & 0b01111101;
    P = P | (X & 0x80);
    P = P | ((X == 0) ? 0x02 : 0x00);
	return 0;
}

// C8       nz----  2   INY     INC Y       Y=Y+1
uint8_t INY(uint8_t op, uint8_t arg0, uint8_t arg1)
{
    Y++;
    PC++;
    tick(2);
    P = P & 0b01111101;
    P = P | (Y & 0x80);
    P = P | ((Y == 0) ? 0x02 : 0x00);
	return 0;
}

// .................................................
// DECREMENT BY ONE
// .................................................
uint8_t DEC(uint8_t op, uint8_t arg0, uint8_t arg1)
{
    uint16_t addr;
    switch(op)
    {
    // C6 nn    nz----  5   DEC nn      DEC [nn]        [nn]=[nn]+1
    case 0xC6:
        addr = (uint16_t)arg0;
        PC += 2;
        tick(5);
        break;
    // D6 nn    nz----  6   DEC nn,X    DEC [nn+X]      [nn+X]=[nn+X]+1
    case 0xD6:
        addr = (uint16_t)(arg0 + X);
        PC += 2;
        tick(6);
        break;
    // CE nn nn nz----  6   DEC nnnn    DEC [nnnn]      [nnnn]=[nnnn]+1
    case 0xCE:
        addr = (((uint16_t)arg1) << 8) + arg0;
        PC += 3;
        tick(6);
        break;
    // DE nn nn nz----  7   DEC nnnn,X  DEC [nnnn+X]    [nnnn+X]=[nnnn+X]+1
    case 0xDE:
        addr = (((uint16_t)arg1) << 8) + arg0 + X;
        PC += 3;
        tick(7);
        break;
    }
    uint8_t value = read(addr);
    write(addr, --value);
    P = P & 0b01111101;
    P = P | (value & 0x80);
    P = P | ((value == 0) ? 0x02 : 0x00);

    return 0;
}    

// CA       nz----  2   DEX     DEC X       X=X-1
uint8_t DEX(uint8_t op, uint8_t arg0, uint8_t arg1)
{
    X--;
    PC--;
    tick(2);
    P = P & 0b01111101;
    P = P | (X & 0x80);
    P = P | ((X == 0) ? 0x02 : 0x00);
	return 0;
}    // DEX

// 88       nz----  2   DEY     DEC Y       Y=Y-1
uint8_t DEY(uint8_t op, uint8_t arg0, uint8_t arg1)
{
    X--;
    PC--;
    tick(2);
    P = P & 0b01111101;
    P = P | (X & 0x80);
    P = P | ((X == 0) ? 0x02 : 0x00);
	return 0;
}
