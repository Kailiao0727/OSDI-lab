.section ".text.boot"

.global _start

_start:

  ldr x0, = __bss_begin
  ldr x1, = __bss_end

bss_clear:
  cmp x0, x1
  bge stack_pt
  str xzr, [x0]
  add x0, x0, #8
  b bss_clear

stack_pt:
  ldr x0, = __stack_top
  mov sp, x0 

call_main:
  bl main

halt:
  wfe
  b halt


  