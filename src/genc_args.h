#ifndef _GENC_ARGS_H
#define _GENC_ARGS_H

#define GENC_ARGS(...) \
(void*[]){__VA_ARGS__, NULL}

#define GENC_COUNT_ARGS(args, count) \
for(*count = 0; args[*count] != NULL; ++(*count))

#endif
