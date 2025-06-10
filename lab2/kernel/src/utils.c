#include "utils.h"

int strcmp(const char *s1, const char *s2) {
  while (*s1 && (*s1 == *s2)) {
      s1++;
      s2++;
  }
  return *(const unsigned char*)s1 - *(const unsigned char*)s2;
}

int strn_cmp(const char *s1, const char *s2, int n) {
    while (n-- && *s1 && *s2) {
        if (*s1 != *s2) {
            return (*s1 - *s2);
        }
        s1++;
        s2++;
    }
    return 0;
}

unsigned int hex2uint(const char *s, int len) {
    unsigned int r = 0;
    while (len--) {
        r <<= 4;
        if (*s >= '0' && *s <= '9') r |= *s - '0';
        else if (*s >= 'A' && *s <= 'F') r |= *s - 'A' + 10;
        else if (*s >= 'a' && *s <= 'f') r |= *s - 'a' + 10;
        s++;
    }
    return r;
}