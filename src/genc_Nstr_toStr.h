#ifndef _GENC_NSTR_TO_STR_H
#define _GENC_NSTR_TO_STR_H

#include <stdlib.h>
#include <string.h>

/**
 * @file genc_nStrStr.h
 * @author Byeonggon Lee
 * @brief This file contains function genc_NStr_toStr
 */

/**
 * @brief
 * Convert Nstr to Str.
 * @param nStr
 * array of characters without null character.
 * @param nStrLength
 * Length of nStr.
 * @returns
 * Heap allocated pointer of Str.
 */

static inline char* genc_Nstr_toStr(char* nStr, size_t nStrLength) {
    char* str = malloc(nStrLength + 1);
    memcpy(str, nStr, nStrLength);
    str[nStrLength] = '\0';
    return str;
}

#endif
