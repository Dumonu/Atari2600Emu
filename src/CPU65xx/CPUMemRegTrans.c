#include "../a2600.h"
#include "CPUMemRegTrans.h"

// .................................................
// REGISTER/IMMEDITATE TO REGISTER TRANSFER
// .................................................
// A8       nz----  2   TAY     MOV Y,A     Y=A
uint8_t TAY_A8(uint8_t arg0, uint8_t arg1)
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
uint8_t TAX_AA(uint8_t arg0, uint8_t arg1)
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
uint8_t TSX_BA(uint8_t arg0, uint8_t arg1)
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
uint8_t TYA_98(uint8_t arg0, uint8_t arg1)
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
uint8_t TXA_8A(uint8_t arg0, uint8_t arg1)
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
uint8_t TXS_9A(uint8_t arg0, uint8_t arg1)
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
// Load value into A
// A9 nn    nz----  2   LDA #nn  MOV A,nn   A=nn
uint8_t LDA_A9(uint8_t arg0, uint8_t arg1)    // LDA #nn
{
    tick(2);
    PC += 2;
    A = arg0;
    P = P & 0x7D;                   // 0 out the Flags we're setting
    P = P | (A & 0x80);             // Negative/Sign Flag
    P = P | (A != 0 ? 0x00 : 0x02); // Zero Flag
    return 0;
}
// A5 nn    nz----  3   LDA nn  MOV A,[nn]  A=[nn]
uint8_t LDA_A5(uint8_t arg0, uint8_t arg1)    // LDA nn
{
    tick(3);
    PC += 2;
    A = read(arg0);
    P = P & 0x7D;                   // 0 out the Flags we're setting
    P = P | (A & 0x80);             // Negative/Sign Flag
    P = P | (A != 0 ? 0x00 : 0x02); // Zero Flag
    return 0;
}
// B5 nn    nz----  4   LDA nn,X    MOV A,[nn+X]    A=[nn+X]
uint8_t LDA_B5(uint8_t arg0, uint8_t arg1)    // LDA nn,X
{
    tick(4);
    PC += 2;
    A = read((uint8_t)(arg0 + X));
    P = P & 0x7D;                   // 0 out the Flags we're setting
    P = P | (A & 0x80);             // Negative/Sign Flag
    P = P | (A != 0 ? 0x00 : 0x02); // Zero Flag
    return 0;
}
// AD nn nn nz----  4   LDA nnnn    MOV A,[nnnn]    A=[nnnn]
uint8_t LDA_AD(uint8_t arg0, uint8_t arg1)    // LDA nnnn
{
    tick(4);
    PC += 3;
    uint16_t addr = (((uint16_t)arg1) << 8) + arg0;
    A = read(addr);
    P = P & 0x7D;                   // 0 out the Flags we're setting
    P = P | (A & 0x80);             // Negative/Sign Flag
    P = P | (A != 0 ? 0x00 : 0x02); // Zero Flag
    return 0;
}
// BD nn nn nz----  4*  LDA nnnn,X  MOV A,[nnnn+X]  A=[nnnn+X]
uint8_t LDA_BD(uint8_t arg0, uint8_t arg1)    // LDA nnnn,X
{
    PC += 3;
    uint16_t addr = (((uint16_t)arg1) << 8) + arg0 + X;
    tick((addr >> 8) > arg1 ? 5 : 4);
    A = read(addr);
    P = P & 0x7D;                   // 0 out the Flags we're setting
    P = P | (A & 0x80);             // Negative/Sign Flag
    P = P | (A != 0 ? 0x00 : 0x02); // Zero Flag
    return 0;
}
// B9 nn nn nz----  4*  LDA nnnn,Y  MOV A,[nnnn+Y]  A=[nnnn+Y]
uint8_t LDA_B9(uint8_t arg0, uint8_t arg1)    // LDA nnnn,Y
{
    PC += 3;
    addr = (((uint16_t)arg1) << 8) + arg0 + Y;
    tick((addr >> 8) > arg1 ? 5 : 4);
    A = read(addr);
    P = P & 0x7D;                   // 0 out the Flags we're setting
    P = P | (A & 0x80);             // Negative/Sign Flag
    P = P | (A != 0 ? 0x00 : 0x02); // Zero Flag
    return 0;
}
// A1 nn    nz----  6   LDA (nn,X)  MOV A,[[nn+X]]  A=[word[nn+X]]
uint8_t LDA_A1(uint8_t arg0, uint8_t arg1)    // LDA (nn,X)
{
    PC += 2;
    tick(6);
    A = read(((uint16_t)(read((uint8_t)(arg0 + X + 1))) << 8) + read((uint8_t)(arg0 + X)));
    P = P & 0x7D;                   // 0 out the Flags we're setting
    P = P | (A & 0x80);             // Negative/Sign Flag
    P = P | (A != 0 ? 0x00 : 0x02); // Zero Flag
    return 0;
}
// B1 nn    nz----  5*  LDA (nn),Y  MOV A,[[nn]+Y]  A=[word[nn]+Y]
uint8_t LDA_B1(uint8_t arg0, uint8_t arg1)    // LDA (nn),Y
{
    PC += 2;
    uint16_t addr = (uint16_t)(read((uint8_t)(arg0 + 1)) << 8) + read(arg0);
    tick(((addr + Y) >> 8) > (addr >> 8) ? 6 : 5);
    A = read(addr + Y);
    P = P & 0x7D;                   // 0 out the Flags we're setting
    P = P | (A & 0x80);             // Negative/Sign Flag
    P = P | (A != 0 ? 0x00 : 0x02); // Zero Flag
    return 0;
}

// Load value into X
// A2 nn    nz----  2   LDX #nn  MOV X,nn   X=nn
uint8_t LDX_A2(uint8_t arg0, uint8_t arg1)     // LDX #nn
{
    PC += 2;
    tick(2);
    X = arg0;
    P = P & 0x7D;                   // 0 out the Flags we're setting
    P = P | (X & 0x80);             // Negative/Sign Flag
    P = P | (X != 0 ? 0x00 : 0x02); // Zero Flag
    return 0;
}
// A6 nn    nz----  3   LDX nn  MOV X,[nn]  X=[nn]
uint8_t LDX_A6(uint8_t arg0, uint8_t arg1)     // LDX nn
{
    tick(3);
    PC += 2;
    X = read(arg0);
    P = P & 0x7D;                   // 0 out the Flags we're setting
    P = P | (X & 0x80);             // Negative/Sign Flag
    P = P | (X != 0 ? 0x00 : 0x02); // Zero Flag
    return 0;
}
// B6 nn    nz----  4   LDX nn,Y    MOV X,[nn+Y]    X=[nn+Y]
uint8_t LDX_B6(uint8_t arg0, uint8_t arg1)     // LDX nn,Y
{
    tick(4);
    PC += 2;
    X = read((uint8_t)(arg0 + Y));
    P = P & 0x7D;                   // 0 out the Flags we're setting
    P = P | (X & 0x80);             // Negative/Sign Flag
    P = P | (X != 0 ? 0x00 : 0x02); // Zero Flag
    return 0;
}
// AE nn nn nz----  4   LDX nnnn    MOV X,[nnnn]    X=[nnnn]
uint8_t LDX_AE(uint8_t arg0, uint8_t arg1)     // LDX nnnn
{
    tick(4);
    PC += 3;
    uint16_t addr = (((uint16_t)arg1) << 8) + arg0;
    X = read(addr);
    P = P & 0x7D;                   // 0 out the Flags we're setting
    P = P | (X & 0x80);             // Negative/Sign Flag
    P = P | (X != 0 ? 0x00 : 0x02); // Zero Flag
    return 0;
}
// BE nn nn nz----  4*  LDX nnnn,Y  MOV X,[nnnn+Y]  X=[nnnn+Y]
uint8_t LDX_BE(uint8_t arg0, uint8_t arg1)     // LDX nnnn,Y
{
    PC += 3;
    addr = (((uint16_t)arg1) << 8) + arg0 + Y;
    tick((addr >> 8) > arg1 ? 5 : 4);
    X = read(addr);
    P = P & 0x7D;                   // 0 out the Flags we're setting
    P = P | (X & 0x80);             // Negative/Sign Flag
    P = P | (X != 0 ? 0x00 : 0x02); // Zero Flag
    return 0;
}

// Load value into Y
// A0 nn    nz----  2   LDY #nn  MOV Y,nn   Y=nn
uint8_t LDY_A0(uint8_t arg0, uint8_t arg1)    // LDY #nn
{
    PC += 2;
    tick(2);
    Y = arg0;
    P = P & 0x7D;                   // 0 out the Flags we're setting
    P = P | (Y & 0x80);             // Negative/Sign Flag
    P = P | (Y != 0 ? 0x00 : 0x02); // Zero Flag
    return 0;
}
// A4 nn    nz----  3   LDY nn  MOV Y,[nn]  Y=[nn]
uint8_t LDY_A4(uint8_t arg0, uint8_t arg1)    // LDY nn
{
    tick(3);
    PC += 2;
    Y = read(arg0);
    P = P & 0x7D;                   // 0 out the Flags we're setting
    P = P | (Y & 0x80);             // Negative/Sign Flag
    P = P | (Y != 0 ? 0x00 : 0x02); // Zero Flag
    return 0;
}
// B4 nn    nz----  4   LDY nn,X    MOV Y,[nn+X]    Y=[nn+X]
uint8_t LDY_B4(uint8_t arg0, uint8_t arg1)    // LDY nn,X
{
    tick(4);
    PC += 2;
    Y = read((uint8_t)(arg0 + X));
    P = P & 0x7D;                   // 0 out the Flags we're setting
    P = P | (Y & 0x80);             // Negative/Sign Flag
    P = P | (Y != 0 ? 0x00 : 0x02); // Zero Flag
    return 0;
}
// AC nn nn nz----  4   LDY nnnn    MOV Y,[nnnn]    Y=[nnnn]
uint8_t LDY_AC(uint8_t arg0, uint8_t arg1)    // LDY nnnn
{
    tick(4);
    PC += 3;
    uint16_t addr = (((uint16_t)arg1) << 8) + arg0;
    Y = read(addr);
    P = P & 0x7D;                   // 0 out the Flags we're setting
    P = P | (Y & 0x80);             // Negative/Sign Flag
    P = P | (Y != 0 ? 0x00 : 0x02); // Zero Flag
    return 0;
}
// BC nn nn nz----  4*  LDY nnnn,X  MOV Y,[nnnn+X]  Y=[nnnn+X]
uint8_t LDY_BC(uint8_t arg0, uint8_t arg1)    // LDY nnnn,X
{
    PC += 3;
    addr = (((uint16_t)arg1) << 8) + arg0 + X;
    tick((addr >> 8) > arg1 ? 5 : 4);
    Y = read(addr);
    P = P & 0x7D;                   // 0 out the Flags we're setting
    P = P | (Y & 0x80);             // Negative/Sign Flag
    P = P | (Y != 0 ? 0x00 : 0x02); // Zero Flag
    return 0;
}

// .................................................
// STORE REGISTER IN MEMORY
// .................................................
// Store A in memory
// 85 nn    ------  3   STA nn      MOV [nn],A  [nn]=A
uint8_t STA_85(uint8_t arg0, uint8_t arg1)     // STA nn
{
    tick(3);
    PC += 2;
    write(arg0, A);
    return 0;
}
// 95 nn    ------  4   STA nn,X    MOV [nn+X],A    [nn+X]=A
uint8_t STA_95(uint8_t arg0, uint8_t arg1)     // STA nn,X
{
    tick(4);
    PC += 2;
    write((uint8_t)(arg0 + X), A);
    return 0;
}
// 8D nn nn ------  4   STA nnnn    MOV [nnnn],A    [nnnn]=A
uint8_t STA_8D(uint8_t arg0, uint8_t arg1)     // STA nnnn
{
    tick(4);
    PC += 3;
    write((uint16_t)(arg1 << 8) + arg0, A);
    return 0;
}
// 9D nn nn ------  5   STA nnnn,X  MOV [nnnn+X],A  [nnnn+X]=A
uint8_t STA_9D(uint8_t arg0, uint8_t arg1)     // STA nnnn,X
{
    tick(5);
    PC += 3;
    write((uint16_t)(arg1 << 8) + arg0 + X, A);
    return 0;
}
// 99 nn nn ------  5   STA nnnn,Y  MOV [nnnn+Y],A  [nnnn+Y]=A
uint8_t STA_99(uint8_t arg0, uint8_t arg1)     // STA nnnn,Y
{
    tick(5);
    PC += 3;
    write((uint16_t)(arg1 << 8) + arg0 + Y, A);
    return 0;
}
// 81 nn    ------  6   STA (nn,X)  MOV [[nn+X]],A  [word[nn+X]]=A
uint8_t STA_81(uint8_t arg0, uint8_t arg1)     // STA (nn,X)
{
    tick(6);
    uint16_t addr = (uint16_t)(read((uint8_t)(arg0 + X + 1)) << 8) + read((uint8_t)(arg0 + X));
    PC += 2;
    write(addr, A);
    return 0;
}
// 91 nn    ------  6   STA (nn),Y  MOV [[nn]+Y],A  [word[nn]+Y]=Y
uint8_t STA_91(uint8_t arg0, uint8_t arg1)     // STA (nn),Y
{
    tick(6);
    uint16_t addr = (uint16_t)(read((uint8_t)(arg0 + 1)) << 8) + read(arg0);
    PC += 2;
    write(addr + Y, A);
    return 0;
}

// Store X in memory
// 86 nn    ------  3   STX nn      MOV [nn],X  [nn]=X
uint8_t STX_86(uint8_t arg0, uint8_t arg1)     // STX nn
{
    tick(3);
    PC += 2;
    write(arg0, X);
    return 0;
}
// 96 nn    ------  4   STX nn,Y    MOV [nn+Y],X    [nn+Y]=X
uint8_t STX_96(uint8_t arg0, uint8_t arg1)     // STX nn,Y
{
    tick(4);
    PC += 2;
    write((uint8_t)(arg0 + Y), X);
    return 0;
}
// 8E nn nn ------  4   STX nnnn    MOV [nnnn],X    [nnnn]=X
uint8_t STX_8E(uint8_t arg0, uint8_t arg1)     // STX nnnn
{
    tick(4);
    PC += 3;
    write((uint16_t)(arg1 << 8) + arg0, X);
    return 0;
}

// Store Y in memory
// 84 nn    ------  3   STY nn      MOV [nn],Y  [nn]=Y
uint8_t STY_84(uint8_t arg0, uint8_t arg1)     // STY nn
{
    tick(3);
    PC += 2;
    write(arg0, Y);
    return 0;
}
// 94 nn    ------  4   STY nn,X    MOV [nn+X],Y    [nn+X]=Y
uint8_t STY_94(uint8_t arg0, uint8_t arg1)     // STY nn,X
{
    tick(4);
    PC += 2;
    write((uint8_t)(arg0 + X), Y);
    return 0;
}
// 8C nn nn ------  4   STY nnnn    MOV [nnnn],Y    [nnnn]=Y
uint8_t STY_8C(uint8_t arg0, uint8_t arg1)     // STY nnnn
{
    tick(4);
    PC += 3;
    write((uint16_t)(arg1 << 8) + arg0, Y);
    return 0;
}

// .................................................
// PUSH/PULL
// .................................................
// 48       ------  3   PHA     PUSH A      [S]=A, S=S-1
uint8_t PHA_48(uint8_t arg0, uint8_t arg1)
{
    write(0x0100 | S--, A);
    tick(3);
    PC += 1;
    return 0;
}

// 08       ------  3   PHP     PUSH P      [S]=P, S=S-1 (flags)
uint8_t PHP_08(uint8_t arg0, uint8_t arg1)
{
    write(0x0100 | S--, P);
    tick(3);
    PC += 1;
	return 0;
}    

// 68       nz----  3   PLA     POP A       S=S+1, A=[S]
uint8_t PLA_68(uint8_t arg0, uint8_t arg1)
{
    A = read(0x0100 | ++S);
    P = P & 0x7D;                   // 0 out the Flags we're setting
    P = P | (A & 0x80);             // Negative/Sign Flag
    P = P | (A != 0 ? 0x00 : 0x02); // Zero Flag
	return 0;
}   
// 28       nzcidv  3   PLP     POP P       S=S+1, P=[S]
uint8_t PLP_28(uint8_t arg0, uint8_t arg1)
{
    P = read(0x0100 | ++S);
	return 0;
}    
