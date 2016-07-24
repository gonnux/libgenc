#ifndef _GONC_STRING_H
#define _GONC_STRING_H

#include <string.h>
#include <libgonc/config.h>

struct gonc_string
{
    char* chars;
    size_t length;
};

#define GONC_STRING_GET_CHARS(string) \
(string)->value

#define GONC_STRING_GET_LENGTH(string) \
(string)->length

#define GONC_STRING_SET(string, _chars)         \
do                                              \
{                                               \
    (string)->chars = _chars;                   \
    (string)->length = strlen((string)->chars); \
}                                               \
while(0)

#define GONC_STRING_SET2(string, _chars, _length) \
do                                                \
{                                                 \
    (string)->chars = _chars;                     \
    (string)->length = _length;                   \
}                                                 \
while(0)

#endif
