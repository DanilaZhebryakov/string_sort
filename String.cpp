#include "String.h"
#include "asserts.h"
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>

int Strcmp(const String* a, const String* b){
    return strcmp(a->chars, b->chars);
}

int Strcmpe(const String* a, const String* b){
    const char* a_ptr = a->chars + a->length;
    const char* b_ptr = b->chars + b->length;
    while(*a_ptr == *b_ptr && a_ptr >= a->chars && b_ptr >= b->chars){
        a_ptr--;b_ptr--;
    }
    if(a_ptr < a->chars){
        if(b_ptr < b->chars){
            return 0;
        }
        return -1;
    }
    if(b_ptr < b->chars){
        return 1;
    }
    return *a_ptr - *b_ptr;
}


String* split( String file_content, int* nlines, char separator) {
    assert_ret_err( file_content.chars != nullptr, nullptr, EFAULT);

    *nlines = countLines(file_content.chars);
    assert_retn(nlines != 0);

    String* lines = (String*)calloc( *nlines, sizeof(String));
    assert_retn(lines != nullptr);

    lines[0].chars = file_content.chars;
    int line_index = 1, line_size = 0;
    for (int i = 0; file_content.chars[i] != '\0'; i++) {
        if (file_content.chars[i] == separator) {
            file_content.chars[i] = '\0';
            lines[line_index].chars = &file_content.chars[i+1];
            lines[line_index-1].length = line_size;

            line_size = 0;
            line_index++;
        }
        else line_size++;
    }
    lines[line_index-1].length = line_size;

    return lines;
}

int countLines(char* str){
    assert_ret_err(str != nullptr, 0, EFAULT);
    int nlines = 1;
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == '\n') {
            nlines++;
        }
    }
    return nlines;
}

int lstrip(String* str,char target_char){
    assert_ret(target_char != '\0', 0);
    int char_count = 0;
    while(*(str->chars) == target_char){
        str->chars++;
        str->length--;
        char_count++;
    }
    return char_count;
}
