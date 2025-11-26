#include "string_c.h"

char *my_strchr(const char *str, int c) { // *str - массив символов, int c - число по каждому символу
    char *result = NULL; // обнуляем переменную

    while(*str != '\0') {   //пока не конец строки
        if(*str == (char)c) { //сравнение номера нашего символа с его реальной цифрой
            result = (char *)str; //если нашли - записали в переменную result
            break; // выходим из функции

        }
        str++; // если не нашли переходим к следующему символу
    }
    return result; //выводим результат 
}