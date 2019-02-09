#ifndef _GENC_BYTES_H
#define _GENC_BYTES_H

#include <stdint.h>

#define GENC_BYTES_REVERSE(bytes, size, outBytes) { \
    for(size_t index = 0; index != size; ++index) { \
        (outBytes)[index] = (bytes)[size - index - 1]; \
    } \
}

#endif
