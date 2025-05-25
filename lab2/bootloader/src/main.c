#include "uart.h"
#include "boot.h"
#include "gpio.h"
#include "peripherals.h"

int main() {
  gpio_init();
  uart_init();

  int r = uart_rcv_kernel();
  if (r == 0) {
    jump_to_kernel();
  } 
  else{
    while(1) {};
  }
  
  uart_puts("Dont print\n");
  
  return 0;
}