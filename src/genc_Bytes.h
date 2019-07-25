#ifndef _GENC_BYTES_H
#define _GENC_BYTES_H

#include <string.h>

#define GENC_BYTES_REV_COPY(bytes, size, outBytes) { \
    for(size_t idx = 0; idx != size; ++idx) \
        (outBytes)[idx] = (bytes)[size - idx - 1]; \
}

#define GENC_BYTES_COPY(bytes, size, outBytes) \
    memcpy(outBytes, bytes, size);

#endif
