#include "mailbox.h"
#include "peripherals.h"

#define MAILBOX_BASE    (PBASE + 0xb880)

#define MAILBOX_READ    ((volatile unsigned int*)(MAILBOX_BASE))
#define MAILBOX_STATUS  ((volatile unsigned int*)(MAILBOX_BASE + 0x18))
#define MAILBOX_WRITE   ((volatile unsigned int*)(MAILBOX_BASE + 0x20))

#define MAILBOX_EMPTY   0x40000000
#define MAILBOX_FULL    0x80000000
#define MAILBOX_RESPONSE   0x80000000

volatile unsigned int  __attribute__((aligned(16))) mailbox[36];

int mailbox_call(unsigned char ch) {
  unsigned int r = (((unsigned int)((unsigned long)&mailbox)&~0xF) | (ch&0xF));
    /* wait until we can write to the mailbox */
    do{asm volatile("nop");}while(*MAILBOX_STATUS & MAILBOX_FULL);
    /* write the address of our message to the mailbox with channel identifier */
    *MAILBOX_WRITE = r;
    /* now wait for the response */
    while(1) {
        /* is there a response? */
        do{asm volatile("nop");}while(*MAILBOX_STATUS & MAILBOX_EMPTY);
        /* is it a response to our message? */
        if(r == *MAILBOX_READ)
            /* is it a valid successful response? */
            return mailbox[1]==MAILBOX_RESPONSE;
    }
    return 0;
}

void get_board_revision(){
  mailbox[0] = 7 * 4; // buffer size in bytes
  mailbox[1] = REQUEST_CODE;
  // tags begin
  mailbox[2] = GET_BOARD_REVISION; // tag identifier
  mailbox[3] = 4; // maximum of request and response value buffer's length.
  mailbox[4] = TAG_REQUEST_CODE;
  mailbox[5] = 0; // value buffer
  // tags end
  mailbox[6] = END_TAG;

  mailbox_call(8); // message passing procedure call, you should implement it following the 6 steps provided above.

  // printf("0x%x\n", mailbox[5]); // it should be 0xa020d3 for rpi3 b+
}

void get_arm_memory() {
  mailbox[0] = 8 * 4;                 // Total size in bytes
  mailbox[1] = REQUEST_CODE;          // Request code

  mailbox[2] = GET_ARM_MEMORY;        // Tag identifier
  mailbox[3] = 8;                     // Value buffer size in bytes (2 * u32)
  mailbox[4] = TAG_REQUEST_CODE;      // Request code
  mailbox[5] = 0;                     // To be filled: base address
  mailbox[6] = 0;                     // To be filled: size in bytes

  mailbox[7] = END_TAG;               // End tag
  mailbox_call(8);
}

