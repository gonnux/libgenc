#ifndef _GENC_N_STR_STR_H
#define _GENC_N_STR_STR_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

static inline int genc_nStrStr(char* nString1, size_t nString1Length, char* string2) {
    char* string1 = malloc(nString1Length + 1);
    memcpy(string1, nString1, nString1Length);
    string1[nString1Length] = '\0';
    return strstr(string1, string2) - string1;
}

#endif
