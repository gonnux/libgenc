#ifndef _GENC_SIPHASH_H
#define _GENC_SIPHASH_H

#include "genc_Bits.h"

#define GENC_SIPHASH_ROUND(v0, v1, v2, v3) { \
    v0 += v1; \
    v1 = GENC_BITS_ROTL(v1, 64, 13); \
    v1 ^= v0; \
    v0 = GENC_BITS_ROTL(v0, 64, 32); \
    v2 += v3; \
    v3 = GENC_BITS_ROTL(v3, 64, 16); \
    v3 ^= v2; \
    v0 += v3; \
    v3 = GENC_BITS_ROTL(v3, 64, 21); \
    v3 ^= v0; \
    v2 += v1; \
    v1 = GENC_BITS_ROTL(v1, 64, 17); \
    v1 ^= v2; \
    v2 = GENC_BITS_ROTL(v2, 64, 32); \
}

#endif
