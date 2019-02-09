#ifndef _GENC_BYTES_H
#define _GENC_BYTES_H

#define <stdint.h>

#define GENC_BYTES_REVERSE(bytes, size) { \
    uint8_t tmp; \
    for(size_t index = 0; index != size; ++index) { \
        if(index == size - index - 1 || (bytes)[index] == (bytes)[size - index - 1]) \
            break; \
        tmp = (bytes)[index]; \
	(bytes)[index] = (bytes)[size - index - 1]; \
        (bytes)[size - index - 1] = (bytes)[index]; \
    } \
}

#endif
