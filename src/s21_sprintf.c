#include <stdio.h>
#include <stdarg.h>
int s21_sprintf(char* buff, const char* format, ...);
int int_to_char(int value, char* str);

int main(){
char buffer[100];
char* str = "world";
s21_sprintf(buffer, "Hello, %d!", -10);
printf("%s", buffer);
}

int s21_sprintf(char* buff, const char* format, ...){
    va_list ap;
    va_start(ap, format);
    char* out = buff;
    while(*format){
        if(*format == '%'){
            format++;
            if(*format == 's'){
                char* x = va_arg(ap, char *);
                while(*x){
                    *out++ = *x++;
                }
            format++;
            }
            if(*format == 'd'){
                int x = va_arg(ap, int);
                int len = int_to_char(x, out);
                out+= len;
            }
            format++;
        }
        *out++ = *format++; 
    }
    va_end(ap);
    *out = '\0';
    return out - buff;

}

int int_to_char(int value, char* str){
    char buffer[32];
    int number = 0;
    int negative = 0;
    int i = 0;
    if(value == 0){
        buffer[0] = 0 + '0';
    }
    else{
    if(value < 0){
        negative = 1;
        value = -value;
    }
    while(value != 0){
        number = value % 10;
        buffer[i] = number + '0';
        value /= 10;
        i++;
    }
    if(negative){
        *str++ = '-';
    }
    for(int j = i - 1; j >= 0; j--){
        *str++ = buffer[j];
    }
    *str = '\0';
}
return negative ? i + 1 : i;
}
