#ifndef _GENC_BYTES_H
#define _GENC_BYTES_H

#include <string.h>

#define GENC_BYTES_REVERSE_COPY(bytes, size, outBytes) { \
    for(size_t index = 0; index != size; ++index) \
        (outBytes)[index] = (bytes)[size - index - 1]; \
}

#define GENC_BYTES_COPY(bytes, size, outBytes) \
    mempcpy(outBytes, bytes, size);

#endif
