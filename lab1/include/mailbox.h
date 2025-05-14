#ifndef MAILBOX_H
#define MAILBOX_H

#include "peripherals.h"
#include "uart.h"

extern volatile unsigned int mailbox[36];

#define GET_BOARD_REVISION  0x00010002
#define GET_ARM_MEMORY     0x00010005

#define REQUEST_CODE        0x00000000
#define REQUEST_SUCCEED     0x80000000
#define REQUEST_FAILED      0x80000001
#define TAG_REQUEST_CODE    0x00000000
#define END_TAG             0x00000000

void get_board_revision();
void get_arm_memory();
int mailbox_call(unsigned char ch);

#endif