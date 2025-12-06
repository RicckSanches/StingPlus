#include "string_c.h"
#include "s21_error.h"
#include <string.h>
#include <stdlib.h> 


//strchr находит первое вхождение символа в строке
char *s21_strchr(const char *str, int c) { 
    char *result = NULL; 
    while(*str != '\0') {  
        if(*str == (char)c) { 
            result = (char *)str; 
            break; 
        }
        str++; 
    }
    return result; 
}


//strrchr находит последнее вхождение строки
char *s21_strrchr(const char *str, int c) {
    char *result_strchr = NULL;
    
    do { 

        if(*str == (char)c){

            result_strchr = (char *)str;
            
            /*
            Разница в том, что мы не выходим из цикла, а доходим до последнего совпадения и выводим текст после нее
            */
       
        }

        str++;

        if(*str == '\0' && c == (int)'\0'){

            result_strchr = (char *)str;

        }

    } while (*str != '\0');

    return result_strchr;
}


//Вычисляет длину начального сегмента str1, который полностью состоит из символов, не входящих в str2.

size_t s21_strcspn(const char *str1, const char *str2) { 

    size_t result_strcspn = 0;
    int is_end = 0;
    //printf("%zu %zu\n", s21_strlen(str1), s21_strlen(str2));

    for(size_t i = 0; i < s21_strlen(str1);i++) {

        for(size_t j = 0; j < s21_strlen(str2); j++){
            //printf("%c %c\n", str1[i], str2[j]);
            
            if(str1[i] == str2[j]){
                is_end = 1;
                break;
            }
             
        }

        if(is_end == 1) {
            break;
        }
          
        result_strcspn++;
    }

    
    return result_strcspn;

}


//Выполняет поиск во внутреннем массиве номера ошибки errnum и возвращает указатель на строку с сообщением об ошибке.
char *s21_strerror(int errnum) { 
    char *buffer = malloc(sizeof(char) * 1024);
    
    if (errnum < NUMBER_OF_ERRORS && errnum >= 0) {
        strncpy(buffer, s21_error_array[errnum], 1024);
    } else {
    sprintf(buffer, "%s %d", UNKNOWN, errnum);
    }
    return buffer;
}
