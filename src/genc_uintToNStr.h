#ifndef _GENC_UINT_TO_N_STR
#define _GENC_UINT_TO_N_STR

#include <stdlib.h>
#include <stdio.h>
static inline size_t genc_uIntToNStr(int _uInteger, int base, char** string) {
    size_t length = 0;

    if(base == 10 || base == 16) {
        int uInteger = _uInteger;
        do {
            uInteger /= base;
            ++length;
        }
        while(uInteger > 0);
        uInteger = _uInteger;

        *string = malloc((length + 1) * sizeof(char));
        for(size_t index = 0; index != length; ++index) {
            int remainder = uInteger % base;
            if(remainder < 10)
                (*string)[length - index - 1] = '0' + remainder;
            else
                (*string)[length - index - 1] = 'A' + remainder - 10;
            uInteger /= base;
        }
    }
    (*string)[length] = '\0';

    return length;
}

#endif
