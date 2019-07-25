#ifndef _GENC_SIPHASH_H
#define _GENC_SIPHASH_H

#include <stdint.h>
#include "genc_Bits.h"
#include "genc_Bytes.h"

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

#define GENC_SIPHASH_HASH(input, size, key, hash) { \
    const uint8_t* inputVar = input; \
    uint64_t v0 = 0x736f6d6570736575ULL; \
    uint64_t v1 = 0x646f72616e646f6dULL; \
    uint64_t v2 = 0x6c7967656e657261ULL; \
    uint64_t v3 = 0x7465646279746573ULL; \
    uint64_t k0; \
    uint64_t k1; \
    GENC_BYTES_COPY(key, sizeof(uint64_t), &k0); \
    GENC_BYTES_COPY(key + 8, sizeof(uint64_t), &k1); \
    v3 ^= k1; \
    v2 ^= k0; \
    v1 ^= k1; \
    v0 ^= k0; \
    const int remSize = size % sizeof(uint64_t); \
    const uint8_t* end = inputVar + size - remSize; \
    for(uint64_t block; inputVar != end; inputVar += sizeof(uint64_t)) { \
        GENC_BYTES_COPY(inputVar, sizeof(uint64_t), &block); \
        v3 ^= block; \
        for(size_t idx = 0; idx < 2; ++idx) \
            GENC_SIPHASH_ROUND(v0, v1, v2, v3); \
        v0 ^= block; \
    } \
    *(hash) = ((uint64_t)size) << 56; \
    switch (remSize) { \
    case 7: \
        *(hash) |= ((uint64_t)inputVar[6]) << 48; \
    case 6: \
        *(hash) |= ((uint64_t)inputVar[5]) << 40; \
    case 5: \
        *(hash) |= ((uint64_t)inputVar[4]) << 32; \
    case 4: \
        *(hash) |= ((uint64_t)inputVar[3]) << 24; \
    case 3: \
        *(hash) |= ((uint64_t)inputVar[2]) << 16; \
    case 2: \
        *(hash) |= ((uint64_t)inputVar[1]) << 8; \
    case 1: \
        *(hash) |= ((uint64_t)inputVar[0]); \
        break; \
    case 0: \
        break; \
    } \
    v3 ^= *(hash); \
    for(size_t idx = 0; idx < 2; ++idx) \
        GENC_SIPHASH_ROUND(v0, v1, v2, v3); \
    v0 ^= *(hash); \
    v2 ^= 0xff; \
    for(size_t idx = 0; idx < 4; ++idx) \
        GENC_SIPHASH_ROUND(v0, v1, v2, v3); \
    *(hash) = v0 ^ v1 ^ v2 ^ v3; \
}

#endif
