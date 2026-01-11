#include "s21_string.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <ctype.h>


int main() {
    char str[100];
    s21_sprintf(str, "wads%c wds%cwdas", '22', '55');
    printf("%s\n", str);
    return 0;
}

