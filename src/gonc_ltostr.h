#ifndef _GONC_LTOSTR
#define _GONC_LTOSTR

#include <stdlib.h>
#include <stdio.h>
static inline size_t gonc_ltostr(long _l, int base, char** str)
{
    size_t length = 0;
    long l = _l;
    do
    {
        l /= 10;
        ++length;
    }
    while(l > 0);
    l = _l;

    *str = malloc((length + 1) * sizeof(char));
    for(size_t index = 0; index != length; ++index)
    {
        (*str)[length - index - 1] = '0' + l % 10;
        l /= 10;
    }
    (*str)[length] = '\0';

    return length;
}

#endif
