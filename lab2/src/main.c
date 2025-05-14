#include "gpio.h"
#include "uart.h"
#include "shell.h"

int main () {
  gpio_init();
  uart_init();
  shell_run();
  return 0;
}