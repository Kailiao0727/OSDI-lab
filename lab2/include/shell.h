#ifndef SHELL_H
#define SHELL_H

#include "uart.h"

void shell_run();
void execute_command(const char *input);

#endif
