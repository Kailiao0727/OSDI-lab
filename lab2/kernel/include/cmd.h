#ifndef CMD_H
#define CMD_H

typedef struct {
  char *name;        // Command name (e.g., "reboot")
  void (*func)(void);  // Function to execute
} Command;

extern const Command commands[];

void cmd_help();
void cmd_hello();
void cmd_mailbox();
void cmd_reboot();
void cmd_null();
void reset(int);
void set(long, unsigned int);
void qemu_reboot();
void cmd_ls();
void cmd_cat();

#endif