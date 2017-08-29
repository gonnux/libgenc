#ifndef _GENC_N_STR_N_STR_H
#define _GENC_N_STR_N_STR_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/**
 * @file genc_nStrNStr.h
 * @author Byeonggon Lee
 * @brief This file contains function genc_nStrNStr
 */

/**
 * @brief
 * Find a string in another string.
 * @param nString1
 * Same as haystack in strstr().
 * @param nString1Length
 * Length of nString1.
 * @param nString2
 * Same as needle in strstr().
 * @param nString2Length
 * Length of nString2.
 * @returns
 * Index of the first match of the substring.
 */

static inline int genc_nStrNStr(char* nString1, size_t nString1Length, char* nString2, size_t nString2Length) {
    char* string1 = malloc(nString1Length + 1);
    memcpy(string1, nString1, nString1Length);
    string1[nString1Length] = '\0';
    char* string2 = malloc(nString2Length + 1);
    memcpy(string2, nString2, nString2Length);
    string2[nString2Length] = '\0';
    char* result = strstr(string1, string2);
    free(string1);
    free(string2);
    if(result == NULL)
        return -1;
    return result - string1;
}

#endif
