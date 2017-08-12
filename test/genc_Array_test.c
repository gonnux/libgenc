#include "../src/genc_Array.h"
#include <stdio.h>

struct integer_array {
    GENC_ARRAY(int);
};

int main() {
    struct integer_array ia;
    GENC_ARRAY_INIT(&ia, 10);
    for(int i = 0; i < GENC_ARRAY_SIZE(&ia); ++i) {
        GENC_ARRAY_SET(&ia, i, i * 100);
        printf("element: %d size: %u\n", GENC_ARRAY_GET(&ia, i), GENC_ARRAY_SIZE(&ia));
    }
    GENC_ARRAY_FOR_EACH(&ia, i) {
        printf("%d\n", GENC_ARRAY_GET(&ia, i));
    }
}
