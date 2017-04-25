#include "a2600.h"
#include "CPUMemRegTrans.h"

// .................................................
// REGISTER/IMMEDITATE TO REGISTER TRANSFER
// .................................................
// A8       nz----  2   TAY     MOV Y,A     Y=A
uint8_t TAY(uint8_t op, uint8_t arg0, uint8_t arg1)
{
    Y = A;                          // Y = A
    P = P & 0x7D;                   // 0 out the Flags we're setting
    P = P | (Y & 0x80);             // Negative/Sign Flag
    P = P | (Y != 0 ? 0x00 : 0x02); // Zero Flag
    ++PC;
    tick(2);
    return 0;
}    
// AA       nz----  2   TAX     MOV X,A     X=A
uint8_t TAX(uint8_t op, uint8_t arg0, uint8_t arg1)
{
    X = A;                          // X = A
    P = P & 0x7D;                   // 0 out the Flags we're setting
    P = P | (X & 0x80);             // Negative/Sign Flag
    P = P | (X != 0 ? 0x00 : 0x02); // Zero Flag
    ++PC;
    tick(2);
    return 0;
}
// BA       nz----  2   TSX     MOV X,S     X=S
uint8_t TSX(uint8_t op, uint8_t arg0, uint8_t arg1)
{
    X = S;                          // Y = A
    P = P & 0x7D;                   // 0 out the Flags we're setting
    P = P | (X & 0x80);             // Negative/Sign Flag
    P = P | (X != 0 ? 0x00 : 0x02); // Zero Flag
    ++PC;
    tick(2);
    return 0;
}
// 98       nz----  2   TYA     MOV A,Y     A=Y
uint8_t TYA(uint8_t op, uint8_t arg0, uint8_t arg1)
{
    A = Y;                          // A = Y
    P = P & 0x7D;                   // 0 out the Flags we're setting
    P = P | (A & 0x80);             // Negative/Sign Flag
    P = P | (A != 0 ? 0x00 : 0x02); // Zero Flag
    ++PC;
    tick(2);
    return 0;
}
// 8A       nz----  2   TXA     MOV A,X     A=X
uint8_t TXA(uint8_t op, uint8_t arg0, uint8_t arg1)
{
    A = X;                          // A = X
    P = P & 0x7D;                   // 0 out the Flags we're setting
    P = P | (A & 0x80);             // Negative/Sign Flag
    P = P | (A != 0 ? 0x00 : 0x02); // Zero Flag
    ++PC;
    tick(2);
    return 0;
}
// 9A       ------  2   TXS     MOV S,X     S=X
uint8_t TXS(uint8_t op, uint8_t arg0, uint8_t arg1)
{
    S = X;                          // A = Y
    ++PC;
    tick(2);
    return 0;
}
                                                        // LDA #nn
                                                        // LDX #nn
                                                        // LDY #nn

// .................................................
// LOAD REGISTER FROM MEMORY
// .................................................
uint8_t LDA(uint8_t op, uint8_t arg0, uint8_t arg1)
{
    uint8_t src = 0;
    switch(op)
    {
    // A9 nn    nz----  2   LDA #nn  MOV A,nn   A=nn
    case 0xA9:
        src = arg0;
        tick(2);
        PC += 2;
        break;
    // A5 nn    nz----  3   LDA nn  MOV A,[nn]  A=[nn]
    case 0xA5:
        src = read(arg0);
        tick(3);
        PC += 2;
        break;
    // B5 nn    nz----  4   LDA nn,X    MOV A,[nn+X]    A=[nn+X]
    case 0xB5:
        src = read((uint8_t)(arg0 + X));
        tick(4);
        PC += 2;
        break;
    // AD nn nn nz----  4   LDA nnnn    MOV A,[nnnn]    A=[nnnn]
    case 0xAD:
        uint16_t addr = (((uint16_t)arg1) << 8) + arg0;
        src = read(addr);
        tick(4);
        PC += 3;
        break;
    // BD nn nn nz----  4*  LDA nnnn,X  MOV A,[nnnn+X]  A=[nnnn+X]
    case 0xBD:
        uint16_t addr = (((uint16_t)arg1) << 8) + arg0 + X;
        src = read(addr);
        tick((addr >> 8) > arg1 ? 5 : 4);
        PC += 3;
        break;
    // B9 nn nn nz----  4*  LDA nnnn,Y  MOV A,[nnnn+Y]  A=[nnnn+Y]
    case 0xB9:
        uint16_t addr = (((uint16_t)arg1) << 8) + arg0 + X;
        src = read(addr);
        tick((addr >> 8) > arg1 ? 5 : 4);
        PC += 3;
        break;
    // A1 nn    nz----  6   LDA (nn,X)  MOV A,[[nn+X]]  A=[word[nn+X]]
    case 0xA1:
        src = read(((uint16_t)(read(arg0 + X + 1)) << 8) + read(arg0 + X));
        tick(6);
        PC += 2;
        break;
    // B1 nn    nz----  5*  LDA (nn),Y  MOV A,[[nn]+Y]  A=[word[nn]+Y]
    case 0xB1:
        uint16_t addr = (uint16_t)(read(arg0 + 1) << 8) + read(arg0);
        src = read(addr + Y);
        tick(((addr + Y) >> 8) > (addr >> 8) ? 6 : 5);
        PC += 2;
        break; 
    }
    A = src;
    P = P & 0x7D;                   // 0 out the Flags we're setting
    P = P | (A & 0x80);             // Negative/Sign Flag
    P = P | (A != 0 ? 0x00 : 0x02); // Zero Flag
    return 0;
    
}

uint8_t LDX(uint8_t op, uint8_t arg0, uint8_t arg1)
{
    uint8_t src = 0;
    switch(op)
    {
    // A2 nn    nz----  2   LDX #nn  MOV X,nn   X=nn
    case 0xA2:
        src = arg0;
        tick(2);
        PC += 2;
        break;
    // A6 nn    nz----  3   LDX nn  MOV X,[nn]  X=[nn]
    case 0xA6:
        src = read(arg0);
        tick(3);
        PC += 2;
        break;
    // B6 nn    nz----  4   LDX nn,Y    MOV X,[nn+Y]    X=[nn+Y]
    case 0xB6:
        src = read((uint8_t)(arg0 + Y));
        tick(4);
        PC += 2;
        break;
    // AE nn nn nz----  4   LDX nnnn    MOV X,[nnnn]    X=[nnnn]
    case 0xAE:
        uint16_t addr = (((uint16_t)arg1) << 8) + arg0;
        src = read(addr);
        tick(4);
        PC += 3;
        break;
    // BE nn nn nz----  4*  LDX nnnn,Y  MOV X,[nnnn+Y]  X=[nnnn+Y]
    case 0xBE:
        uint16_t addr = (((uint16_t)arg1) << 8) + arg0 + Y;
        src = read(addr);
        tick((addr >> 8) > arg1 ? 5 : 4);
        PC += 3;
        break;
    }
    X = src;
    P = P & 0x7D;                   // 0 out the Flags we're setting
    P = P | (X & 0x80);             // Negative/Sign Flag
    P = P | (X != 0 ? 0x00 : 0x02); // Zero Flag
    return 0;

}
// LDX nn
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
