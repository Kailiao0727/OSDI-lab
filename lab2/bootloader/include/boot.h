#ifndef BOOT_H
#define BOOT_H
#include "uart.h"
#include "type.h"

void uart_send_bytes(const uint8_t *data, uint32_t size);
void uart_read_bytes(uint8_t *buffer, uint32_t size);

int uart_rcv_kernel(void);
void jump_to_kernel(void);
uint32_t calculate_crc32(const uint8_t *data, uint32_t len);

#endif