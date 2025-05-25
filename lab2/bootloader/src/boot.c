#include "boot.h"
#include "uart.h"
#include "type.h"

#define HEADER_MAGIC 0x544F4F42
#define KERNEL_ADDR 0x80000

/* Send multiple bytes over UART */
void uart_send_bytes(const uint8_t *data, uint32_t size)
{
  while (size--) {
    uart_putc(*data++);
  }
}

/* Read multiple bytes from UART */
void uart_read_bytes(uint8_t *buffer, uint32_t size)
{
  while (size--) {
    *buffer++ = uart_getc();
  }
}

typedef struct {
  unsigned int magic;
  unsigned int size;
  unsigned int checksum;
} boot_header;

int uart_rcv_kernel(void) {
  boot_header header;
  uint8_t *buffer = (uint8_t*)KERNEL_ADDR;

  uart_puts("Waiting for kernel...\n");

  /* Read the header */
  uart_read_bytes((uint8_t *)&header, sizeof(header));

  /* Check the magic number */
  if (header.magic != HEADER_MAGIC) {
    uart_putc(0x15); // NAK
    return -1;
  }

  if(header.size > 0x100000) { // 1MB limit
    uart_puts("Kernel too large\n");
    return -1;
  }

  uart_putc(0x06); // ACK

  /* Read the kernel */
  uart_read_bytes(buffer, header.size);

  /* Check checksum */
  if(calculate_crc32(buffer, header.size) != header.checksum) {
    uart_puts("Checksum fail\n");
    return -1;
  }

  /* Send the kernel to the specified address */
  uart_send_bytes(buffer, header.size);

  uart_puts("Kernel loaded successfully\n");
  // asm volatile("mov sp, %0" : : "r"(KERNEL_ADDR)); // Reset stack
  return 0;
}

void jump_to_kernel(void) {
  void (*kernel)(void) = (void (*)(void))KERNEL_ADDR;
  kernel();
  uart_puts("Kernel execution finished\n");
  while (1) {
    // Infinite loop to prevent returning to the bootloader
  }
}

uint32_t calculate_crc32(const uint8_t *data, uint32_t len) {
  uint32_t crc = 0xFFFFFFFF;
  while(len--) {
      crc ^= *data++;
      for(uint8_t i=0; i<8; i++) 
          crc = (crc>>1) ^ (0xEDB88320 & -(crc&1));
  }
  return ~crc;
}