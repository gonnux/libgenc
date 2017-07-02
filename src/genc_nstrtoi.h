#ifndef _GENC_NSTRTOI
#define _GENC_NSTRTOI

#include <stdlib.h>
#include <stdio.h>
static inline int genc_nstrtoi(char* string, size_t length)
{
    int intValue = 0;
    int multiplier = 1;
    for(int index = length - 1; index >= 0; --index, multiplier *= 10)
    {
        if(string[index] - '0' < 0 || string[index] - '0' > 9)
            return -1;
        intValue += (string[index] - '0') * multiplier;
    }
    return intValue;
}

#endif
