#include "s21_string.h"
#include "s21_error.h"

s21_size s21_strlen(const char *str) {
    s21_size res = 0;
    if (str != s21_NULL) {
        const char *p = str;
        while (*p != '\0') p++;
        res = p - str;
    } else {
        res = -1;
    }

    return res;
}


void *s21_memcpy(void *dest, const void *src, s21_size n) {
    unsigned char* d = (unsigned char*) dest;
    unsigned char* s = (unsigned char*) src;

    for (s21_size i = 0; i < n; i++) {
        d[i] = s[i];
    }
    return dest;
}

void *s21_memset(void *str, int c, s21_size n) {
    unsigned char* string = str;
    unsigned char symbol = c;
    for (s21_size i = 0; i < n; i++) {
        string[i] = symbol;
    }
    return str;
}

int s21_memcmp(const void *str1, const void *str2, s21_size n) {
    int result = 0;
    int are_equal = 1;
    const unsigned char* string1 = str1;
    const unsigned char* string2 = str2;

    for (s21_size i = 0; i < n && are_equal; i++) {
        if (string1[i] != string2[i]) {
            result = string1[i] - string2[i];
            are_equal = 0;
        }
    }
    return result;
}

char *s21_strncpy(char *dest, const char *src, s21_size n) {
    int is_end = 0;
    for (s21_size i = 0; i < n && !is_end; i++) {
        if (src[i] != '\0') {
            dest[i] = src[i];
        }
        else {
            dest[i] = '\0';
            is_end = 1;
        }
    }
    return dest;
}

char *s21_strncat(char *dest, const char *src, s21_size n) {
    s21_size dest_len = s21_strlen(dest);
    for (s21_size i = 0; i < n; i++) {
        dest[dest_len+i] = src[i];
    }
    return dest;
}

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

char *s21_strrchr(const char *str, int c) {
    char *result_strchr = NULL;
    
    do { 

        if(*str == (char)c){

            result_strchr = (char *)str;

        }

        str++;

        if(*str == '\0' && c == (int)'\0'){

            result_strchr = (char *)str;

        }

    } while (*str != '\0');

    return result_strchr;
}
size_t s21_strcspn(const char *str1, const char *str2) { 
    size_t result_strcspn = 0;
    int is_end = 0;

    for(size_t i = 0; i < s21_strlen(str1);i++) {

        for(size_t j = 0; j < s21_strlen(str2); j++){
            
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
char *s21_strerror(int errnum) { 
    char *buffer = malloc(sizeof(char) * 1024);
    
    if (errnum < NUMBER_OF_ERRORS && errnum >= 0) {
        s21_strncpy(buffer, s21_error_array[errnum], 1024);
    } else {
    s21_sprintf(buffer, "%s %d", UNKNOWN, errnum);
    }
    return buffer;
}

void* s21_memchr(const void* str, int c, s21_size n) {
    const unsigned char* pstr = str;
    unsigned char target = (unsigned char)c;
    for (s21_size i = 0; i < n; i++) {
      if (pstr[i] == target) {
        return (void*)(pstr + i);
      }
    }
    return s21_NULL;
  }
  
  int s21_strncmp(const char* str1, const char* str2, s21_size n) {
    int result = 0;
    for (s21_size i = 0; i < n; i++) {
      unsigned char c1 = str1[i];
      unsigned char c2 = str2[i];
      if (result == 0) {
        if (c1 != c2) {
          result = c1 - c2;
        } else if (c1 == '\0') {
          result = 0;
        }
      }
    }
    return result;
  }
    
  char* s21_strpbrk(const char* str1, const char* str2) {
    if (!str1 || !str2) return s21_NULL;
    while (*str1) {
      const char* pstr2 = str2;
      while (*pstr2) {
        if (*str1 == *pstr2) return (char*)str1;
        pstr2++;
      }
      str1++;
    }
    return s21_NULL;
  }
  
  char* s21_strstr(const char* haystack, const char* needle) {
    s21_size nl = s21_strlen(needle);
    s21_size hl = s21_strlen(haystack);
    if (*needle == '\0') return (char*)haystack;
    if (*haystack == '\0') return s21_NULL;
    if (nl > hl) return s21_NULL;
    for (s21_size i = 0; i <= hl - nl; i++) {
      s21_size j = 0;
      while (needle[j] && haystack[i + j] == needle[j]) {
        j++;
      }
      if (needle[j] == '\0') {
        return (char*)(haystack + i);
      }
    }
    return s21_NULL;
  }
  
  char* s21_strtok(char* str, const char* delim) {
    static char* save = s21_NULL;
    char* token_start = s21_NULL;
    if (str != s21_NULL) {
      save = str;
    }
    if (save == s21_NULL || *save == '\0') {
      return s21_NULL;
    }
    while (*save && s21_strchr(delim, *save) != s21_NULL) {
      save++;
    }
    if (*save == '\0') return s21_NULL;
    token_start = save;
    while (*save && s21_strchr(delim, *save) == s21_NULL) {
      save++;
    }
    if (*save) {
      *save = '\0';
      save++;
    }
    return token_start;
  }