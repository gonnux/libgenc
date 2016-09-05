#ifndef _GONC_NSTRNCASECMP_H
#define _GONC_NSTRNCASECMP_H

#include <ctype.h>
#include <stddef.h>

static inline int gonc_nstrncasecmp(const char* s1, size_t n1, const char* s2, size_t n2)
{
    for(size_t index = 0; index < n1 && index < n2; ++index)
    {
        if(toupper(s1[index]) != toupper(s2[index]))
            return toupper(s1[index]) - toupper(s2[index]);
    }
    return n1 - n2;
}

#endif
