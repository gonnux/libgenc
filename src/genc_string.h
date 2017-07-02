#ifndef _GENC_STRING_H
#define _GENC_STRING_H

#include <stdbool.h>
#include <string.h>

struct genc_string
{
    char* chars;
    size_t length;
    bool freeable;
};

#define GENC_STRING_GET_CHARS(string) \
(string)->value

#define GENC_STRING_GET_LENGTH(string) \
(string)->length

#define GENC_STRING_IS_FREEABLE(string) \
(string)->freeable

#define GENC_STRING_SET(string, _chars, _freeable) \
do                                                 \
{                                                  \
    (string)->chars = _chars;                      \
    (string)->length = strlen((string)->chars);    \
    (string)->freeable = _freeable;                \
}                                                  \
while(0)

#define GENC_STRING_SET2(string, _chars, _length, _freeable) \
do                                                           \
{                                                            \
    (string)->chars = _chars;                                \
    (string)->length = _length;                              \
    (string)->freeable = _freeable;                          \
}                                                            \
while(0)

#endif
