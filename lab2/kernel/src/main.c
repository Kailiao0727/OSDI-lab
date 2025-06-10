#include "gpio.h"
#include "uart.h"
#include "shell.h"
#include "cpio.h"

int main () {
  gpio_init();
  uart_init();
  #ifdef ON_RPI3
    cpio_base_addr = 0x20000000;
  #else
    cpio_base_addr = 0x8000000;
  #endif
  shell_run();
  return 0;
}