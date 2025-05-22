#include "uart.h"
#include "boot.h"
#include "gpio.h"
#include "peripherals.h"

int main() {
  gpio_init();
  uart_init();
  uart_puts("Waiting for kernel...\n");

  uart_rcv_kernel();
  jump_to_kernel();
  uart_puts("Dont print\n");
  
  return 0;
}