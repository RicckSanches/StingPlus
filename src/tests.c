#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "string_c.h"
#include "s21_error.h"




int test_strchr() {

    int err = 0;


    char text[] = "Hello World";
    char* result = s21_strchr(text, 'W');

    if(result != text + 6*sizeof(char)) {
       err++;
    }

    char text2[] = "Hello World";
    char* result1 = s21_strchr(text2, 'o');

    if(result1 != text2 + 4*sizeof(char)) {
        err++;
    }

    char text3[] = "Hello World";
    char* result3 = s21_strchr(text3, 'k');

    if(result3 != NULL) {
        err++;
    }

    char text4[] = "";
    char* result4 = s21_strchr(text4, 'W');

    if(result4 != NULL) {
        err++;
    }

    char text5[] = "Hello World";
    char* result5 = s21_strchr(text5, ' ');

    if(result5 != text5 + 5*sizeof(char)) {
        err++;
    }

    printf("%d\n", err);

    return err;
}

int test_strrchr() {

    int err = 0;

    char text1[] = "Hello World";
    char* result1 = s21_strrchr(text1, 'o');

    if(result1 != text1 + 7*sizeof(char)) {
        printf("ошибка тут1:%d\n", err);
        err++;
    }

    char text2[] = "mississippi";
    char* result2 = s21_strrchr(text2, 's');

    if(result2 != text2 + 6*sizeof(char)) {
        printf("ошибка тут2:%d\n", err);
        err++;
    }


    char text3[] = "Hello World";
    char* result3 = s21_strrchr(text3, 'z');

    if(result3 != NULL) {
        printf("ошибка тут3:%d\n", err);
        err++;
    }


    char text4[] = "";
    char* result4 = s21_strrchr(text4, 'a');

    if(result4 != NULL) {
        printf("ошибка тут4:%d\n", err);
        err++;
    }


    char text5[] = "Hello";
    char* result5 = s21_strrchr(text5, '\0');

    if(result5 != text5+5*sizeof(char)) {
        printf("ошибка тут5:%d\n", err);
        err++;
    }
    printf("%d\n", err);

    return err;

}
  
int test_strlen() {
    int err = 0;
    
   
    char text1[] = "Hello World";
    s21_size_t result1 = s21_strlen(text1);
    if(result1 != 12) { 
        err++;
    }
    
    
    char text2[] = "";
    s21_size_t result2 = s21_strlen(text2);
    if(result2 != 1) { 
        err++;
    }
    
    
    char text3[] = "A";
    s21_size_t result3 = s21_strlen(text3);
    if(result3 != 2) {
        err++;
    }
    
   
    char text4[] = "   ";
    s21_size_t result4 = s21_strlen(text4);
    if(result4 != 4) {
        err++;
    }
    
    
    char text5[] = "\t\n";
    s21_size_t result5 = s21_strlen(text5);
    if(result5 != 3) { 
        err++;
    }
    
    
    char text6[] = "This is a very long string for testing purposes";
    s21_size_t result6 = s21_strlen(text6);
    if(result6 != 48) { 
        err++;
    }
    
    
    char text7[] = "Hello\0World";
    s21_size_t result7 = s21_strlen(text7);
    if(result7 != 6) { 
        err++;
    }
    
    
    char text8[] = "1234567890";
    s21_size_t result8 = s21_strlen(text8);
    if(result8 != 11) { 
        err++;
    }
    
    
    char text9[] = "!@#$%^&*()";
    s21_size_t result9 = s21_strlen(text9);
    if(result9 != 11) { 
        err++;
    }
    
    
    char text10[] = "Hello123!@#";
    s21_size_t result10 = s21_strlen(text10);
    if(result10 != 12) { 
        err++;
    }
    
    printf("%d\n", err);

    return err;
}

int test_strcspn() {
    int err = 0;
    
   
    char str1_1[] = "abcdefg";
    char str2_1[] = "xyz";
    s21_size_t result1 = s21_strcspn(str1_1, str2_1);
    if(result1 != 7) { 
        err++;
    }
    
    
    char str1_2[] = "abcdefg";
    char str2_2[] = "a";
    s21_size_t result2 = s21_strcspn(str1_2, str2_2);
    if(result2 != 0) { 
        err++;
    }
    

    char str1_3[] = "abcdefg";
    char str2_3[] = "d";
    s21_size_t result3 = s21_strcspn(str1_3, str2_3);
    if(result3 != 3) { 
        err++;
    }
    
   
    char str1_4[] = "hello123";
    char str2_4[] = "0123456789";
    s21_size_t result4 = s21_strcspn(str1_4, str2_4);
    if(result4 != 5) { 
        err++;
    }
    
    
    char str1_5[] = "abcdefg";
    char str2_5[] = "";
    s21_size_t result5 = s21_strcspn(str1_5, str2_5);
    if(result5 != 7) { 
        err++;
    }
    
    
    char str1_6[] = "";
    char str2_6[] = "abc";
    s21_size_t result6 = s21_strcspn(str1_6, str2_6);
    if(result6 != 0) { 
        err++;
    }
    
    
    char str1_7[] = "";
    char str2_7[] = "";
    s21_size_t result7 = s21_strcspn(str1_7, str2_7);
    if(result7 != 0) {
        err++;
    }
    
    
    char str1_8[] = "abcdef";
    char str2_8[] = "f";
    s21_size_t result8 = s21_strcspn(str1_8, str2_8);
    if(result8 != 5) {
        err++;
    }
    
    
    char str1_9[] = "programming";
    char str2_9[] = "aeiou";
    s21_size_t result9 = s21_strcspn(str1_9, str2_9);
    if(result9 != 2) { 
        err++;
    }
    
    char str1_9b[] = "programming";
    char str2_9b[] = "aeiou";
    s21_size_t result9b = s21_strcspn(str1_9b, str2_9b);
    if(result9b != 2) { 
        err++;
    }
    
   
    char str1_10[] = "abc";
    char str2_10[] = "abcde";
    s21_size_t result10 = s21_strcspn(str1_10, str2_10);
    if(result10 != 0) { 
        err++;
    }
    
   
    char str1_11[] = "hello world!";
    char str2_11[] = " !";
    s21_size_t result11 = s21_strcspn(str1_11, str2_11);
    if(result11 != 5) { 
        err++;
    }
    
  
    char str1_12[] = "test123";
    char str2_12[] = "0123456789";
    s21_size_t result12 = s21_strcspn(str1_12, str2_12);
    if(result12 != 4) {
        err++;
    }

    printf("количество ошибок:%d\n", err);
    
    return err;
}

int test_strerror(){

    int err = 0;


    for(int i = 0; i < NUMBER_OF_ERRORS; i++){
        if(strcmp(s21_strerror(i),strerror(i)) != 0){
            err++;
        }
        ;
        
        //printf("%s\n", strerror(i));
        //printf("%s\n\n", s21_strerror(i));
    }
    printf("%d\n", err);
    return err;

}

int main() {

    test_strchr();
    test_strrchr();
    test_strlen();
    test_strcspn();
    test_strerror();

    return 0;
}


