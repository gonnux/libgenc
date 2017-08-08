#ifndef _GENC_NSTRNSTR
#define _GENC_NSTRNSTR

#include <stdlib.h>
#include <stdio.h>
static inline int genc_nstrnstr(char* string1, size_t string1Length, char* string2, size_t string2Length)
{
    char* ntString1 = malloc(string1Length + 1);
    memcpy(ntString1, string1, string1Length);
    ntstring1[string1Length] = '\0';
    char* ntString2 = malloc(string2Length + 1);
    memcpy(ntString2, string2, string2Length);
    ntstring2[string2Length] = '\0';
    return strstr(ntString1, ntString2) - ntString1;
}

#endif
