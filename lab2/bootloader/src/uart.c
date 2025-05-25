#include "uart.h"

void uart_init() {
    *AUX_ENABLES |= 1;
    *AUX_MU_CNTL_REG = 0;
    *AUX_MU_IER_REG = 0;
    *AUX_MU_LCR_REG = 3;
    *AUX_MU_MCR_REG = 0;
    *AUX_MU_BAUD_REG = 270;

    *AUX_MU_IIR_REG= 6;
    *AUX_MU_CNTL_REG = 3;

    //interrupt
    // *AUX_IRQ |= (1 << 29);
}

char uart_getc(void) {
    while (!(*AUX_MU_LSR_REG & 0x01)); // Wait until data is ready
    return (char)(*AUX_MU_IO_REG & 0xFF); // Read the byte from the UART
}

void uart_putc(char c) {
    while (!(*AUX_MU_LSR_REG & (1 << 5)));
    // Write the character (bottom 8 bits) into the IO register
    *AUX_MU_IO_REG = (unsigned int)c;
}

void uart_puts(const char *s) {
    while (*s) {
        // if (*s == '\n')
        //     uart_putc('\r');  // for proper newline display
        uart_putc(*s++);
    }
}

void uart_gets(char *buf, int maxlen) {
    int i = 0;
    while (i < maxlen - 1) {
        char c = uart_getc();
        if (c == '\r' || c == '\n') {
            uart_putc('\n');
            break;
        } else if (c == 127 || c == '\b') {  // handle backspace
            if (i > 0) {
                uart_putc('\b');
                uart_putc(' ');
                uart_putc('\b');
                i--;
            }
        } else {
            uart_putc(c);
            buf[i++] = c;
        }
    }
    buf[i] = '\0';
}


void uart_hex(unsigned int d) {
    char hex_chars[] = "0123456789ABCDEF";
    for (int i = 28; i >= 0; i -= 4)
        uart_putc(hex_chars[(d >> i) & 0xF]);
}



