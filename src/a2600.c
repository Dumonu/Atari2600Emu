#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "CPUMemRegTrans.h"
#include "CPUArithLogOps.h"
#include "CPURotShift.h"
#include "CPUJumpCtrl.h"
#include "a2600.h"


int8_t tick(uint8_t cycles)
{
    // The Atari 2600 contains a 1.19 Mhz 65xx Processor
    // That means that each clock cycle takes 840 nanoseconds, so do that.
    struct timespec *delay = {0, cycles * 840};
    return nanosleep(delay, NULL);
}

// ................................................................................................
// ILLEGAL AND UNDEFINED OPCODES
// ................................................................................................
uint8_t ill(uint8_t op, uint8_t arg0, uint8_t arg1)
{
    fprintf(stderr, "Illegal Opcode Called, may be implemented in the future for completeness");
    exit(1);
}

uint8_t und(uint8_t op, uint8_t arg0, uint8_t arg1)
{
    fprintf(stderr, "Undefined Opcode Called");
    exit(1);
}


// ................................................................................................
// MEMORY I/O
// ................................................................................................

uint8_t read(int ind)
{
    switch(ind)
    {
    case default:
        return MEMORY[ind];
        break;
    }
}
void write(int ind, uint8_t val)
{
    switch(ind)
    {
    case default:
        MEMORY[ind] = val;
        break;
    }
}
