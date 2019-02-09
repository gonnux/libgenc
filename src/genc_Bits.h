#ifndef _GENC_BITS_H
#define _GENC_BITS_H

#define GENC_BITS_ROTL(bits, size, count) \
(((bits) << (count)) | ((bits) >> (size - (count))))

#define GENC_BITS_ROTR(bits, size, count) \
(((bits) << (size - (count))) | ((bits) >> (count)))

#endif
