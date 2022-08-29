#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <errno.h>
#include <string.h>

#include "file_read.h"
#include "asserts.h"

size_t getFileSize( FILE* file){
    assert_ret_err(file != nullptr, 0, EFAULT);
    fseek(file, 0, SEEK_END);
    size_t file_size = ftell(file) + 1;
    rewind(file);
    return file_size;
}

String readFile( FILE* file) {
    assert_ret_err(file != nullptr, ((String){nullptr, 0}), EFAULT);

    size_t file_size = getFileSize(file);
    char* file_content = (char*)calloc((file_size + 1), sizeof(char));
    assert_ret(file_content != nullptr, ((String){nullptr, 0}));
    size_t fread_val = fread( file_content, sizeof(char), file_size, file);
    if (errno != 0){
        fprintf(stderr,"Error: fread error \nFile:%s \nLine:%d \nFunc:%s\nExpected %ld chars ,got %ld. \nFunction returns nullptr\n",
                                            __FILE__,__LINE__, __PRETTY_FUNCTION__, file_size, fread_val);
        free(file_content);
        return {nullptr, 0};
    }

    file_content[fread_val] = '\0';
    return {file_content, fread_val};
}
