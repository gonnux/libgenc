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

#define GENC_STRING_GET_CHARS(self) \
(self)->chars

#define GENC_STRING_GET_LENGTH(self) \
(self)->length

#define GENC_STRING_IS_FREEABLE(self) \
(self)->freeable

#define GENC_STRING_SET(self, _chars, _freeable) { \
    (self)->chars = _chars; \
    (self)->length = strlen((self)->chars); \
    (self)->freeable = _freeable; \
}

#define GENC_STRING_SET2(self, _chars, _length, _freeable) { \
    (self)->chars = _chars; \
    (self)->length = _length; \
    (self)->freeable = _freeable; \
}

#define GENC_STRING_FREE(self) { \
    if(GENC_STRING_IS_FREEABLE(self)) { \
        free((self)->chars); \
        (self)->chars = NULL; \
        (self)->freeable = false; \
    } \
}

#endif
