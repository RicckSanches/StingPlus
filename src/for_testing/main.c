//перетащи в src, чтобы проверить функцию

#include <stdio.h>
#include "string_c.h"

int main() {
    char text[] = "Hello World";
    
    char *result = strchr(text, 'W');
    char *result_last = strrchr(text, 'l');


    if (result != NULL) {
        printf("%s\n", result);  //World
        printf("%s\n", result_last); //ld
    }
    
    return 0;
}