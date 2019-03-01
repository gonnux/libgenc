#ifndef _GENC_GENERIC_H
#define _GENC_GENERIC_H

union genc_Generic {
    int integer;
    unsigned int uInteger;
    double real;
    unsigned double uReal;
    char character;
    unsigned char uCharacter;
    void* pointer;
    void** array;
};

#endif
