#ifndef _GONC_DEBUG_H
#define _GONC_DEBUG_H

#include <err.h>

#ifndef DEBUG

#define GONC_DEBUG(fmt, ...)

#else

#define GONC_DEBUG(fmt, ...) warnx("%s: %u: " fmt, __FILE__, __LINE__, ##__VA_ARGS__)

#endif
#endif
