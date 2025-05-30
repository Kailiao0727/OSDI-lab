#ifndef UART_H
#define UART_H

#include "peripherals.h"

#define AUX_ENABLES     ((volatile unsigned int*)(PBASE + 0x00215004))
#define AUX_MU_IO_REG   ((volatile unsigned int*)(PBASE + 0x00215040))
#define AUX_MU_IER_REG  ((volatile unsigned int*)(PBASE + 0x00215044))
#define AUX_MU_IIR_REG  ((volatile unsigned int*)(PBASE + 0x00215048))
#define AUX_MU_LCR_REG  ((volatile unsigned int*)(PBASE + 0x0021504C))
#define AUX_MU_MCR_REG  ((volatile unsigned int*)(PBASE + 0x00215050))
#define AUX_MU_LSR_REG  ((volatile unsigned int*)(PBASE + 0x00215054))
#define AUX_MU_CNTL_REG ((volatile unsigned int*)(PBASE + 0x00215060))
#define AUX_MU_BAUD_REG ((volatile unsigned int*)(PBASE + 0x00215068))

#define AUX_MU_LSR_REG  ((volatile unsigned int*)(PBASE + 0x00215054))

#define AUX_IRQ   (volatile unsigned int*)(PBASE + 0x00215000)

void uart_init();
char uart_getc(void);
void uart_putc(char);
void uart_puts(const char *s);
void uart_gets(char *buf, int maxlen);
void uart_hex(unsigned int d);



#endif