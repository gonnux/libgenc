#ifndef _GENC_BITS_H
#define _GENC_BITS_H

#define GENC_BITS_ROTL(bits, size, count) \
(uint64_t)(((bits) << (count)) | ((bits) >> (size - (count))))

#define GENC_BITS_ROTR(bits, size, count) \
(uint64_t)(((bits) << (size - (count))) | ((bits) >> (count)))

#endif
