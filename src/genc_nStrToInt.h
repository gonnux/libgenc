#ifndef _GENC_N_STR_TO_INT
#define _GENC_N_STR_TO_INT

#include <stdlib.h>
#include <stdio.h>
static inline int genc_nStrToInt(char* string, size_t length) {
    int integer = 0;
    int multiplier = 1;
    bool isNegative = false;
    for(int index = length - 1; index >= 0; --index, multiplier *= 10) {
        if(index == 0 && (string[0] == '+' || string[0] == '-')) {
            isNegative = string[0] == '-';
            break;
        } else if(string[index] - '0' < 0 || string[index] - '0' > 9)
            return -1;
        integer += (string[index] - '0') * multiplier;
    }
    if(isNegative)
        return integer * -1;
    return integer;
}

#endif
