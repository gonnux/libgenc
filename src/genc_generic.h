#ifndef _GENC_GENERIC_H
#define _GENC_GENERIC_H

union genc_Generic {
    int integer;
    unsigned int uInteger;
    void* pointer;
    void** array;
};

#endif
