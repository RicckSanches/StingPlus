#include "s21_string.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main() {
    char str1[20] = "sadwa  ";
    char str2[] = "awds";

    s21_strncat(str1, str2, 4);
    printf("%s\n", str1);

    return 0;
}