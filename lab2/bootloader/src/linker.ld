
ENTRY(_start)

SECTIONS {
  . = 0x60000;
  
  __loader_begin = .;

  .text : { KEEP(*(.text.boot)) *(.text) }

  .rodata : { *(.rodata) }

  .data : { *(.data) }

  .bss : { 
    . = ALIGN(0x8);
    __bss_begin = .;
    *(.bss*) 
    __bss_end = .;
  }

  __loader_end = .;  

  . = 0x78000;
  __stack_top = .;

}

__bss_size = (__bss_end - __bss_begin);
__loader_size = (__loader_end - __loader_begin);