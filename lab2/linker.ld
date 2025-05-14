STACKSIZE = 0x80000;
HEAPSIZE = 0x80000;

ENTRY(_start)

SECTIONS {
  . = 0x80000;

  .text.boot : { *(.text.boot) }

  .text : { *(.text) }

  .rodata : { *(.rodata) }

  .data : { *(.data) }

  .bss : { 
    . = ALIGN(0x8);
    __bss_begin = .;
    *(.bss*) 
    __bss_end = .;
  }

  .heap : {
    . = ALIGN(16);
    . += HEAPSIZE;
  }
  
  .stack : {
    . = ALIGN(16);
    __stack_bottom = .;
    . += STACKSIZE;
    __stack_top = .;
  }
}