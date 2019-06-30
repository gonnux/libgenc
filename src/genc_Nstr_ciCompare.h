#ifndef _GENC_NSTR_CI_COMPARE_H
#define _GENC_NSTR_CI_COMPARE_H

#include <ctype.h>
#include <stddef.h>

static inline int genc_Nstr_ciCompare(const char* s1, size_t n1, const char* s2, size_t n2) {
    for(size_t idx = 0; idx < n1 && idx < n2; ++idx) {
        if(toupper(s1[idx]) != toupper(s2[idx]))
            return toupper(s1[idx]) - toupper(s2[idx]);
    }
    return n1 - n2;
}

#endif
