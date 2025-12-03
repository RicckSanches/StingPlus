#include "s21_string.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main() {
    char a[] = "test";
    char b[] = "test";

    int result = s21_memcmp(a, b, 4);
    printf("%d\n", result);

    result = memcmp(a, b, 4);
    printf("%d\n", result);

    return 0;
}