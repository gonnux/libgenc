#ifndef _GENC_N_STR_N_STR_H
#define _GENC_N_STR_N_STR_H

#include <stdlib.h>
#include <stdio.h>
static inline int genc_nStrNStr(char* nString1, size_t nString1Length, char* nString2, size_t nString2Length) {
    char* string1 = malloc(nString1Length + 1);
    memcpy(string1, nString1, nString1Length);
    ntnString1[nString1Length] = '\0';
    char* string2 = malloc(nString2Length + 1);
    memcpy(string2, nString2, nString2Length);
    ntnString2[nString2Length] = '\0';
    return strstr(string1, string2) - string1;
}

#endif
