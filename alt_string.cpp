#include <stdio.h>

#include "asserts.h"


size_t alt_strlen(const char* str) {
    assert_ret(str != nullptr,0);
    size_t i = 0;
    while (str[i] != '\0')
        i++;
    return i;
}

char* alt_strcpy(char* dst, const char* src) {
    char* r = dst;
    assert_retnull(dst != nullptr);
    assert_retnull(src != nullptr);
    while (*src != '\0') {
        *dst = *src;
        dst++;
        src++;
    }
    *dst = *src;

    return r;
}

char* alt_strchr(char* str, int c) {
    assert_retnull(str != nullptr);
    while ((*str) != '\0' && (*str) != c)
        str++;

    if ((*str) == c)
        return str;
    else
        return nullptr;
}

int alt_strcmp(char* a,char * b){
    while ((*a == *b) && (*a != 0)) {
        a++; b++;
    }
    return (*a - *b);
}

char* alt_strcat(char* dst, const char* src) {
    assert_retnull(dst != nullptr);
    assert_retnull(src != nullptr);
    char* r = dst;
    while (*dst != '\0')
        dst++;
    alt_strcpy(dst, src);
    return r;
}
