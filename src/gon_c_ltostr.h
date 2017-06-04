#ifndef _GON_C_LTOSTR
#define _GON_C_LTOSTR

#include <stdlib.h>
#include <stdio.h>
static inline size_t gon_c_ltostr(long _l, int base, char** str)
{
    size_t length = 0;

    if(base == 10 || base == 16)
    {
        long l = _l;
        do
        {
            l /= base;
            ++length;
        }
        while(l > 0);
        l = _l;

        *str = malloc((length + 1) * sizeof(char));
        for(size_t index = 0; index != length; ++index)
        {
            long remainder = l % base;
            if(remainder < 10)
                (*str)[length - index - 1] = '0' + remainder;
            else
                (*str)[length - index - 1] = 'A' + remainder - 10;
            l /= base;
        }
    }
    (*str)[length] = '\0';

    return length;
}

#endif
