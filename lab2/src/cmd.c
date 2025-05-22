#include "cmd.h"
#include "mailbox.h"
#include "uart.h"
#include "utils.h"

const Command commands[] = {
  {"help", cmd_help}, 
  {"hello", cmd_hello},
  {"mailbox", cmd_mailbox},
  {"reboot", cmd_reboot},
  {"NULL", cmd_null}
};

void cmd_null() {
  uart_puts("what\n");
}

void cmd_help() {
  uart_puts("help    : print this help menu\n");
  uart_puts("hello   : print Hello World!\n");
  uart_puts("reboot  : reboot the device\n");
  uart_puts("mailbox : print hardware's information\n");
}

void cmd_hello() {
  uart_puts("Hello World!\n");
}

void cmd_mailbox() {
  uart_puts("Mailbox info:\n");
  uart_puts("Board revision: ");
  get_board_revision();
  uart_hex(mailbox[5]);
  uart_puts("\nARM memory base address: ");
  get_arm_memory();
  uart_hex(mailbox[5]);
  uart_puts("\nARM memory size: ");
  uart_hex(mailbox[6]);
  uart_puts("\n");
}

#define PM_PASSWORD 0x5a000000
#define PM_RSTC 0x3F10001c
#define PM_WDOG 0x3F100024

void set(long addr, unsigned int value) {
    volatile unsigned int* point = (unsigned int*)addr;
    *point = value;
}

void reset(int tick) {                 // reboot after watchdog timer expire
    set(PM_RSTC, PM_PASSWORD | 0x20);  // full reset
    set(PM_WDOG, PM_PASSWORD | tick);  // number of watchdog tick
}

void qemu_reboot(void) {
  // asm volatile(
  //   "mov x0, #0x84000009\n"  // PSCI_SYSTEM_RESET
  //   "smc #0"
  // );
}

void cmd_reboot() {
    reset(100);
}