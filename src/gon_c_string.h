#ifndef _GON_C_STRING_H
#define _GON_C_STRING_H

#include <stdbool.h>
#include <string.h>

struct gon_c_string
{
    char* chars;
    size_t length;
    bool freeable;
};

#define GON_C_STRING_GET_CHARS(string) \
(string)->value

#define GON_C_STRING_GET_LENGTH(string) \
(string)->length

#define GON_C_STRING_IS_FREEABLE(string) \
(string)->freeable

#define GON_C_STRING_SET(string, _chars, _freeable) \
do                                                 \
{                                                  \
    (string)->chars = _chars;                      \
    (string)->length = strlen((string)->chars);    \
    (string)->freeable = _freeable;                \
}                                                  \
while(0)

#define GON_C_STRING_SET2(string, _chars, _length, _freeable) \
do                                                           \
{                                                            \
    (string)->chars = _chars;                                \
    (string)->length = _length;                              \
    (string)->freeable = _freeable;                          \
}                                                            \
while(0)

#endif
