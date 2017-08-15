#ifndef _GENC_STR_N_STR_H
#define _GENC_STR_N_STR_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
static inline int genc_strNStr(char* string1, char* nString2, size_t nString2Length) {
    char* string2 = malloc(nString2Length + 1);
    memcpy(string2, nString2, nString2Length);
    string2[nString2Length] = '\0';
    int result = strstr(string1, string2) - string1;
    free(string2);
    return result;
}

#endif
