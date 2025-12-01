//перетащи в src, чтобы проверить функцию

#include <stdio.h>
#include "string_c.h"
#include <string.h>

int main() {
    char text1[] = "He;;o world";
    char text2[] = "skibudu";
    
    //char *result = strchr(text, 'W');
   // char *result_last = strrchr(text, 'l');
    
    
    size_t lenght = my_strcspn(text1, text2);



    printf("%zu", lenght);
    
    return 0;
}