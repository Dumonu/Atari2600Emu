#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "a2600.h"

char *Ptob()
{
    char *ret = (char *) malloc(sizeof(char) * 9);
    uint8_t p = P;
    for(int i = 7; i >= 0; --i)
    {
        ret[i] = 0x30 + (p % 2);
        p /= 2;
    }
    ret[9] = 0;
    return ret;
}

int main(int argc, char **argv)
{
    FILE *in = fopen(argv[1], "r");
    if(!in)
    {
        perror("Failure opening file");
        return errno;
    }

    int c;
    int addr = 0xF000;
    while ((c = fgetc(in)) != EOF)
    {
        MEMORY[addr++] = c;
    }
    MEMORY[addr] = 0x04;

    fclose(in);

    initCPU();

    int r = 0;
    while(r == 0)
    {
        uint8_t op = read(PC);
        uint8_t a0 = read(PC + 1);
        uint8_t a1 = read(PC + 2);
        r = (*ops[op>>4][op & 0xF])(op, a0, a1);
        printf("A: %x\tX: %x\tY: %x\tPC: %x\tS: %x\tP: %s\n", A, X, Y, PC, S, Ptob());
    }

    FILE *out = fopen("dump/mem.bin", "w");
    if(!out)
    {
        perror("Failure creating file");
        return errno;
    }

    for(int i = 0; i < 0xFFFF; ++i)
    {
        if(putc(read(i), out) == EOF)
        {
            perror("Write failed");
        }
    }
    fclose(out);
    return 0;
}
