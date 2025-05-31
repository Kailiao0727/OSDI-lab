.section ".text.boot"

.global _start

_start:
    // relocate bootloader
    ldr x1, =0x80000 
    ldr x2, =__loader_begin // x2 = 0x60000
    ldr w3, =__loader_size  // now in bytes

relocate:
    cbz w3, setting
    ldrb w4, [x1], #1       // load 1 byte from x1 to w4, increment x1
    strb w4, [x2], #1       // store 1 byte to x2, increment x2
    sub w3, w3, #1
    cbnz w3, relocate

setting: 
    ldr x1, =_start
    mov sp, x1
    ldr x1, =__bss_begin
    ldr w2, =__bss_size     // now in bytes

clear_bss: 
    cbz w2, bootloader_main
    strb wzr, [x1], #1      // store zero byte, increment pointer by 1
    sub w2, w2, #1
    cbnz w2, clear_bss

bootloader_main: 
    bl main-0x20000
    b  bootloader_main