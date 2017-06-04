#ifndef _GON_C_UINTTOSTR
#define _GON_C_UINTTOSTR

#include <stdlib.h>
#include <stdio.h>
static inline size_t gon_c_uinttostr(unsigned int _uint, int base, char** str)
{
    size_t length = 0;

    if(base == 10 || base == 16)
    {
        long uint = _uint;
        do
        {
            uint /= base;
            ++length;
        }
        while(uint > 0);
        uint = _uint;

        *str = malloc((length + 1) * sizeof(char));
        for(size_t index = 0; index != length; ++index)
        {
            long remainder = uint % base;
            if(remainder < 10)
                (*str)[length - index - 1] = '0' + remainder;
            else
                (*str)[length - index - 1] = 'A' + remainder - 10;
            uint /= base;
        }
    }
    (*str)[length] = '\0';

    return length;
}

#endif
