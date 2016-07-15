#ifndef _GONC_KEYVAL_H
#define _GONC_KEYVAL_H

#define GONC_KEYVAL(key_type, value_type) \
struct                                    \
{                                         \
    key_type key;                         \
    value_type value;                     \
} gonc_keyval;

#define GONC_KEYVAL_KEY(keyval) \
(keyval)->gonc_keyval.key

#define GONC_KEYVAL_VALUE(keyval) \
(keyval)->gonc_keyval.value

#endif
