#ifndef _GENC_NSTR_TO_INT
#define _GENC_NSTR_TO_INT

#include <stdlib.h>
#include <stdio.h>

static inline int genc_Nstr_toInt(char* nstr, size_t nstrLength) {
    int integer = 0;
    int multiplier = 1;
    bool isNegative = false;
    for(int index = nstrLength - 1; index >= 0; --index, multiplier *= 10) {
        if(index == 0 && (nstr[0] == '+' || nstr[0] == '-')) {
            isNegative = nstr[0] == '-';
            break;
        } else if(nstr[index] - '0' < 0 || nstr[index] - '0' > 9)
            return -1;
        integer += (nstr[index] - '0') * multiplier;
    }
    if(isNegative)
        return integer * -1;
    return integer;
}

#endif
