#ifndef _GENC_INT_TO_N_STR
#define _GENC_INT_TO_N_STR

#include <stdlib.h>
#include <stdio.h>
static inline size_t genc_intToNStr(int _integer, int base, char** string) {
    size_t length = 0;

    if(base == 10 || base == 16) {
        int integer = _integer;
        do {
            integer /= base;
            ++length;
        }
        while(integer > 0);
        integer = _integer;

        *string = malloc((length + 1) * sizeof(char));
        for(size_t index = 0; index != length; ++index) {
            int remainder = integer % base;
            if(remainder < 10)
                (*string)[length - index - 1] = '0' + remainder;
            else
                (*string)[length - index - 1] = 'A' + remainder - 10;
            integer /= base;
        }
    }
    (*string)[length] = '\0';

    return length;
}

#endif
