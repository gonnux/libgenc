#ifndef _GENC_NSTR_COMPARE_H
#define _GENC_NSTR_COMPARE_H

#include <stddef.h>

static inline int genc_Nstr_compare(const char* s1, size_t n1, const char* s2, size_t n2) {
    for(size_t idx = 0; idx < n1 && idx < n2; ++idx) {
        if(s1[idx] != s2[idx])
            return s1[idx] - s2[idx];
    }
    return n1 - n2;
}

#endif
