#ifndef _GENC_STRING_H
#define _GENC_STRING_H

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

struct genc_String {
    char* chars;
    size_t length;
    bool freeable;
};

#define GENC_STRING_GET_CHARS(string) \
(string)->chars

#define GENC_STRING_GET_LENGTH(string) \
(string)->length

#define GENC_STRING_IS_FREEABLE(string) \
(string)->freeable

#define GENC_STRING_SET(string, _chars, _freeable) \
do {                                               \
    (string)->chars = _chars;                      \
    (string)->length = strlen((string)->chars);    \
    (string)->freeable = _freeable;                \
} while(0)

#define GENC_STRING_SET2(string, _chars, _length, _freeable) \
do {                                                         \
    (string)->chars = _chars;                                \
    (string)->length = _length;                              \
    (string)->freeable = _freeable;                          \
} while(0)

#define GENC_STRING_FREE(string)          \
do {                                      \
    if(GENC_STRING_IS_FREEABLE(string)) { \
        free((string)->chars);            \
        (string)->chars = NULL;           \
        (string)->freeable = false;       \
    }                                     \
} while(0)

#endif
