//перетащи в src, чтобы проверить функцию

#include <stdio.h>
#include "string_c.h"

int main() {
    char text[] = "Hello World";
    
    char *result = my_strchr(text, 'W');

    if (result != NULL) {
        printf("%s\n", result);  //World
    }
    
    return 0;
}