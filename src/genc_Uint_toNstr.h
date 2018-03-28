#ifndef _GENC_UINT_TO_NSTR
#define _GENC_UINT_TO_NSTR

#include <stdlib.h>
static inline size_t genc_Uint_toNstr(int _uInteger, int base, char** string) {
    size_t length = 0;

    if(base == 10 || base == 16) {
        int uInteger = _uInteger;
        do {
            uInteger /= base;
            ++length;
        } while(uInteger > 0);
        uInteger = _uInteger;

        *string = malloc(length * sizeof(char));
        for(size_t index = 0; index != length; ++index) {
            int remainder = uInteger % base;
            if(remainder < 10)
                (*string)[length - index - 1] = '0' + remainder;
            else
                (*string)[length - index - 1] = 'A' + remainder - 10;
            uInteger /= base;
        }
    }
    return length;
}

#endif
