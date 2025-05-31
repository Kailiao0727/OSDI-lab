#include "uart.h"
#include "boot.h"
#include "gpio.h"
#include "peripherals.h"

int main() {
  gpio_init();
  uart_init();
  

  long int s=1000000000;
	while(s--){
		asm volatile("nop");
	}
  uart_puts("Ready...\n");
  
  int r = uart_rcv_kernel();
  while(r != 0) {
    r = uart_rcv_kernel();
  }
  
  s = 1000000000;
  while(s--){
    asm volatile("nop");
  }

  if (r == 0) {
    uart_puts("Jumping to kernel.\n");
    
    jump_to_kernel();
  } 
  else{
    uart_puts("Kernel transfer failed.\n");
    while(1) {};
  }
  
  uart_puts("Dont print\n");
  
  return 0;
}