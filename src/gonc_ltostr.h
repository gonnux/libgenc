#ifndef _GONC_LTOSTR
#define _GONC_LTOSTR

#include <stdlib.h>

#define GONC_LTOSTR(_l, base, str)                  \
do                                                  \
{                                                   \
    size_t length = 0;                              \
    long l = _l;                                    \
    do                                              \
    {                                               \
        l /= 10;                                    \
        ++length;                                   \
    }                                               \
    while(l > 0);                                   \
    l = _l;                                         \
    str = malloc(length * sizeof(char));            \
    for(size_t index = 0; index != length; ++index) \
    {                                               \
        str[length - index - 1] = '0' + l % 10;     \
        l /= 10;                                    \
    }                                               \
}                                                   \
while(0);

#endif
