#include "s21_string.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main() {
    char str[100] = "awdswfasfiuawhfiuanfgiuhwg";
    sprintf(str, "%.2d wdas", 8.92);
    printf("%s\n", str);
    return 0;
}