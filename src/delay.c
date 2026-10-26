#include <delay.h>

#define SYSTEM_TIMER_LOW (volatile unsigned int*)(SYSTEM_TIMER_BASE+0x4)
#define SYSTEM_TIMER_HIGH (volatile unsigned int*)(SYSTEM_TIMER_BASE+0x8)

#define TIMER_CS_M0   (1 << 0)
#define TIMER_CS_M1   (1 << 1)
#define TIMER_CS_M2   (1 << 2)
#define TIMER_CS_M3   (1 << 3)

void delayCycles(unsigned int n) {
    if (n) while (n--) {asm volatile("nop");}
}

void delayUSecs(unsigned int n) {
    register unsigned long f,t,r;

    asm volatile ("mrs %0, cntfrq_el0" : "=r"(f));
    asm volatile ("mrs %0, cntpct_el0" : "=r"(t));

    unsigned long i=((f/1000)*n)/1000;

    do {asm volatile("mrs %0, cntpct_el0" : "=r"(r));} while (r-t<i);
}

unsigned long getSystemTimer() {
    unsigned int h=-1, l;

    h=*SYSTEM_TIMER_HIGH;
    l=*SYSTEM_TIMER_LOW;

    if (h!=*SYSTEM_TIMER_HIGH) {
        h=*SYSTEM_TIMER_HIGH;
        l=*SYSTEM_TIMER_LOW;
    }

    return ((unsigned long) h << 32) | l;
}
