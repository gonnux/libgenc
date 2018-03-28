#ifndef _GENC_GENC_NSTR_FIND_H
#define _GENC_GENC_NSTR_FIND_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/**
 * @file genc_Nstr_find.h
 * @author Byeonggon Lee
 * @brief This file contains function genc_nstr_find
 */

/**
 * @brief
 * Find a nstr in another nstr.
 * @param nstr1
 * Same as haystack in strstr().
 * @param nstr1Length
 * Length of nstr1.
 * @param nstr2
 * Same as needle in strstr().
 * @param nstr2Length
 * Length of nstr2.
 * @returns
 * Index of the first match of the substring.
 */

static inline int genc_Nstr_find(char* nstr1, size_t nstr1Length, char* nstr2, size_t nstr2Length) {
    char* string1 = malloc(nstr1Length + 1);
    memcpy(string1, nstr1, nstr1Length);
    string1[nstr1Length] = '\0';
    char* string2 = malloc(nstr2Length + 1);
    memcpy(string2, nstr2, nstr2Length);
    string2[nstr2Length] = '\0';
    char* result = strstr(string1, string2);
    free(string1);
    free(string2);
    if(result == NULL)
        return -1;
    return result - string1;
}

#endif
