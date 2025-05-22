#include "shell.h"
#include "uart.h"
#include "utils.h"
#include "mailbox.h"
#include "cmd.h"

#define CMD_LEN 128

void shell_run() {

  uart_puts("Welcome to OSC Lab2!\n");


  char cmd[CMD_LEN];

  while (1) {
    uart_puts("# ");
    uart_gets(cmd, CMD_LEN);
    execute_command(cmd);
  }
}

void execute_command(const char *input) {
  if (input[0] == '\0') return;
  
  /* Find matching command */
  for (const Command *cmd = commands; strcmp(cmd->name, "NULL"); cmd++) {
      if (strcmp(input, cmd->name) == 0) {
          cmd->func();
          return;
      }
  }
  if (strcmp(input, "") == 0) {return;}
  
  /* No match found */
  uart_puts("Unknown command: ");
  uart_puts(input);
  uart_puts("\n");
  return;
}