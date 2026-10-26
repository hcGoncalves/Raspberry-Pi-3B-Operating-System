#ifndef DELAY_H
#define DELAY_H

#include <peripheral.h>
#include <stdint.h>

#define SYSTEM_TIMER_BASE (PERIPHERAL_BASE + 0x3000)

void delayCycles(unsigned int n);
void delayUSecs(unsigned int us);
unsigned long getSystemTimer();

#endif // DELAY_H
