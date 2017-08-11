#ifndef _GENC_CASE_COMPARE_N_STR_N_STR_H
#define _GENC_CASE_COMPARE_N_STR_N_STR_H

#include <ctype.h>
#include <stddef.h>

static inline int genc_caseCompareNStr(const char* s1, size_t n1, const char* s2, size_t n2) {
    for(size_t index = 0; index < n1 && index < n2; ++index) {
        if(toupper(s1[index]) != toupper(s2[index]))
            return toupper(s1[index]) - toupper(s2[index]);
    }
    return n1 - n2;
}

#endif
