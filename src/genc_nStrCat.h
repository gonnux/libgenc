#include <string.h>
static inline size_t genc_nStrCat(char* dest, size_t destCapacity, size_t* destSize, const char* src, size_t srcSize) {
    if(*destSize + srcSize < destCapacity) {
        memcpy(dest + *destSize, src, srcSize);
        *destSize += srcSize;
        return 0;
    }
    return -1;
}
