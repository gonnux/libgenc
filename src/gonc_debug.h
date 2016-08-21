#ifndef _GONC_DEBUG_H
#define _GONC_DEBUG_H

#include <err.h>
#include <pthread.h>

#ifndef DEBUG

#define GONC_WARN(fmt, ...)
#define GONC_WARNX(fmt, ...)
#define GONC_ERR(eval, fmt, ...)
#define GONC_TLERR(eval, fmt, ...)
#define GONC_ERRX(eval, fmt, ...)
#define GONC_TLERRX(eval, fmt, ...)

#else

#define GONC_WARN(fmt, ...) warn(fmt, __VA_ARGS__)
#define GONC_WARNX(fmt, ...) warnx(fmt, __VA_ARGS__)
#define GONC_ERR(eval, fmt, ...) err(eval, fmt, __VA_ARGS__)
#define GONC_TLERR(eval, fmt, ...) \
do                                 \
{                                  \
    warn(fmt, __VA_ARGS__);        \
    pthread_exit(eval);            \
}                                  \
while(0)
#define GONC_ERRX(eval, fmt, ...) errx(eval, fmt, __VA_ARGS__)
#define GONC_TLERRX(eval, fmt, ...) \
do                                  \
{                                   \
    warnx(fmt, __VA_ARGS__);        \
    pthread_exit(eval);             \
}                                   \
while(0)

#endif
#endif
