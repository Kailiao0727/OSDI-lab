.global _start

.section ".text.boot"
_start:
  mrs x0, mpidr_el1
  and x1, x0, #0x3
  cmp x1, #0
  bne halt

  ldr x0, = __bss_begin
  ldr x1, = __bss_end

bss_clear:
  cmp x0, x1
  bge stack_pt
  str xzr, [x0]
  add x0, x0, #8
  b bss_clear

//stack location?? overlap  
stack_pt:
  ldr x0, = __stack_top
  mov sp, x0 

call_main:
  bl main

halt:
  wfe
  b halt


  