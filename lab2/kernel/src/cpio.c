#include "cpio.h"
#include "utils.h"
#include "uart.h"

unsigned long cpio_base_addr;


void cpio_ls() {
  const char* ptr =(const char*)cpio_base_addr;
  while(1) {
    struct cpio_newc_header* header = (struct cpio_newc_header*)ptr;
    if (strn_cmp(header->c_magic, "070701", 6) != 0) break;
    unsigned int namesize = hex2uint(header->c_namesize, 8);
    unsigned int filesize = hex2uint(header->c_filesize, 8);
    const char* name = ptr + sizeof(struct cpio_newc_header);
    if (strcmp(name, "TRAILER!!!") == 0) break;
    if (name[0] == '.' && name[1] == '/')
      name += 2;
    uart_puts(name);
    uart_puts("\n");

    ptr +=((sizeof(struct cpio_newc_header)+ namesize + 3) & ~3) + ((filesize + 3) & ~3);
    // const char* name = ptr
    // if(strcmp(name, "TRAILER!!!") == 0) break;
  }
}
void cpio_cat(char* filename) {
  const char* ptr = (const char*)cpio_base_addr;
  while(1) {
    struct cpio_newc_header* header = (struct cpio_newc_header*)ptr;
    if (strn_cmp(header->c_magic, "070701", 6) != 0) break;
    unsigned int namesize = hex2uint(header->c_namesize, 8);
    unsigned int filesize = hex2uint(header->c_filesize, 8);
    const char* name = ptr + sizeof(struct cpio_newc_header);
    if (strcmp(name, "TRAILER!!!") == 0) {
      uart_puts("File not found.\n");
      return;
    }
    if (name[0] == '.' && name[1] == '/')
      name += 2;
    if (strcmp(filename, name) == 0) {
      ptr += ((sizeof(struct cpio_newc_header)+ namesize + 3) & ~3);
      const char* filedata = ptr;
      for(unsigned int i = 0; i < filesize; i++) {
        uart_putc(filedata[i]);
      }
      uart_puts("\n");
      return;
    }
    ptr +=((sizeof(struct cpio_newc_header)+ namesize + 3) & ~3) + ((filesize + 3) & ~3);
  }
}