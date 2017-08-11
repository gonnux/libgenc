#ifndef _GENC_COMPARE_NSTR_H
#define _GENC_COMPARE_NSTR_H

#include <stddef.h>

static inline int genc_compareNStr(const char* s1, size_t n1, const char* s2, size_t n2) {
    for(size_t index = 0; index < n1 && index < n2; ++index) {
        if(s1[index] != s2[index])
            return s1[index] - s2[index];
    }
    return n1 - n2;
}

#endif
