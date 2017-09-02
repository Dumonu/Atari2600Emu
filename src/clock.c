#include <time.h>
#include "clock.h"
#include "a2600.h"

// Runs on a separate thread from the CPU, TIA, and other things
// and send signals on a 1.19MHz frequency. This allows for 
// synchronization between the various distinct parts of the
// Atari 2600.

//CPU Clock: 1.193182 MHz (NTSC)
//Video Color Clock: 3.579545 MHZ (NTSC)

void initClk()
{
    CPUTick = 0;
}

void clkTick()
{
    while(1)
    {
        if(done)
            return;
        struct timespec delay = {0, 838};
        nanosleep(&delay, NULL);
        while(CPUTick); //Wait for CPU to make CPUtick false
                        // i.e. it has recieved last signal
        CPUTick = 1;    // Signal CPU
    }
}
