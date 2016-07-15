#ifndef _GONC_STRING_H
#define _GONC_STRING_H

#include <string.h>

struct gonc_string
{
    char* value;
    size_t length;
};

#define GONC_STRING_GET_VALUE(string) \
(string)->value

#define GONC_STRING_GET_LENGTH(string) \
(string)->length

#define GONC_STRING_SET(string, _value)         \
do                                              \
{                                               \
    (string)->value = _value;                   \
    (string)->length = strlen((string)->value); \
}                                               \
while(0)

#define GONC_STRING_SET2(string, _value, _length) \
do                                                \
{                                                 \
    (string)->value = _value;                     \
    (string)->length = _length;                   \
}                                                 \
while(0)

#endif
