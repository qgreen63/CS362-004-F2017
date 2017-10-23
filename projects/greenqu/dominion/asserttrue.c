#include <stdio.h>

void assertTrue(int expr) {
    if (expr)
        printf("Pass\n");
    else
        printf("Fail\n");
}
