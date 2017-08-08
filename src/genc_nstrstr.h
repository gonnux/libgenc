#ifndef _GENC_NSTRSTR
#define _GENC_NSTRSTR

#include <stdlib.h>
#include <stdio.h>
static inline int genc_nstrstr(char* string1, size_t string1Length, char* string2)
{
    char* ntString1 = malloc(string1Length + 1);
    memcpy(ntString1, string1, string1Length);
    ntstring1[string1Length] = '\0';
    return strstr(ntString1, string2) - ntString1;
}

#endif
