#include "shell.h"
#include "uart.h"
#include "utils.h"
#include "mailbox.h"

#define CMD_LEN 128

void shell_run() {

  uart_puts("Welcome to OSC Lab1!\n");


  char cmd[CMD_LEN];

  while (1) {
    uart_puts("# ");
    uart_gets(cmd, CMD_LEN);

    if (strcmp(cmd, "help") == 0) {
      uart_puts("help    : print this help menu\n");
      uart_puts("hello   : print Hello World!\n");
      uart_puts("mailbox : print hardware's information\n");

    } else if (strcmp(cmd, "hello") == 0) {
      uart_puts("Hello World!\n");

    } else if (strcmp(cmd, "mailbox") == 0) {
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
    } else if (strcmp(cmd, "") == 0) {
      // do nothing, just redraw prompt

    } else {
      uart_puts("Unknown command: ");
      uart_puts(cmd);
      uart_puts("\n");
    }
  }
}