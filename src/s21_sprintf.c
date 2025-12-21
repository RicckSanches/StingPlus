#include <stdio.h>
#include <stdarg.h>
int s21_sprintf(char* buff, const char* format, ...);

int main(){
char buffer[100];
char* str = "world";
s21_sprintf(buffer, "Hello, %s!", str);
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

            }
        }
        *out++ = *format++; 
    }
    va_end(ap);
    *out = '\0';
    return out - buff;

}

