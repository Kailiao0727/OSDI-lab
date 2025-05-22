#include "gpio.h"

void gpio_init() {
  // Set GPIO14 and GPIO15 to ALT5
  unsigned int r = *GPFSEL1;
  r &= ~((7 << 12) | (7 << 15)); // clear bits for GPIO14 and GPIO15
  r |=  (2 << 12) | (2 << 15);   // set ALT5 (010) for GPIO14 and 15
  *GPFSEL1 = r;

  // Disable pull-up/down
  *GPPUD = 0;
  for (int i = 0; i < 150; i++) { asm volatile("nop"); }

  // Clock the control signal into GPIO14 and GPIO15
  *GPPUDCLK0 = (1 << 14) | (1 << 15);
  for (int i = 0; i < 150; i++) { asm volatile("nop"); }

  *GPPUD = 0;
  *GPPUDCLK0 = 0;
}