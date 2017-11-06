#include <stdio.h>

void assertTrue(int expr) {
    if (!expr)
        printf("Fail\n");
}
