#ifndef GPIO_H
#define GPIO_H

#include "peripherals.h"

#define GPFSEL1     ((volatile unsigned int*)(PBASE + 0x00200004))
#define GPPUD       ((volatile unsigned int*)(PBASE + 0x00200094))
#define GPPUDCLK0   ((volatile unsigned int*)(PBASE + 0x00200098))

void gpio_init();

#endif

