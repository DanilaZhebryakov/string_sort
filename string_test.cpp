#include <stdio.h>
#include <string.h>

#include "alt_string.h"
#include "String.h"

int sign(int a){
    if (a < 0) {
        return -1;
    }
    return a > 0;
}

bool runStrlenTest(FILE* file){
    int expected_length = -1;
    char str[100] = {'\0'};

    if (fscanf(file, " strlen %s %d\n", str, &expected_length) != 2) {
        printf("strlen test failed: unexpected end of file or incorrect format\n");
        return false;
    }

    size_t got_length = alt_strlen(str);
    if (got_length != expected_length) {
        printf("strlen test failed: expected length %d got length %d\n", expected_length, got_length);
        printf("on test: str=%s len=%d\n", str, expected_length);
        return false;
    }

    return true;
}

bool runStrcpyTest(FILE* file){
    char dst[100]             = {'\0'};
    char src[100]             = {'\0'};
    char expected_result[100] = {'\0'};

    if (fscanf(file, " strcpy %s %s %s", dst, src, expected_result) != 3) {
        printf("strcpy test failed: unexpected end of file or incorrect format\n");
        return false;
    }

    char* got_result = alt_strcpy(dst,src);
    if (strcmp(got_result, expected_result) != 0) {
        printf("stcrcpy test failed: expected result %s got result %s\n", expected_result, got_result);
        printf("on test: dst=%s src=%s res=%s\n", dst, src, expected_result);
        return false;
    }

    return true;
}

bool runStrcatTest(FILE* file){
    char dst[100]             = {'\0'};
    char src[100]             = {'\0'};
    char expected_result[100] = {'\0'};

    if (fscanf(file, " strcat %s %s %s", dst, src, expected_result) != 3) {
        printf("strcat test failed: unexpected end of file or incorrect format\n");
        return false;
    }

    char* got_result = alt_strcat(dst, src);
    if (strcmp(got_result,expected_result) != 0) {
        printf("strcat test failed: expected result %s got result %s\n", expected_result, got_result);
        printf("on test: dst=%s src=%s res=%s\n", dst, src, expected_result);
        return false;
    }

    return true;
}

bool runStrcmpTest(FILE* file){
    char str_a[100] = {'\0'};
    char str_b[100] = {'\0'};
    int   expected_result = 0;

    if (fscanf(file, " strcmp %s %s %d", str_a, str_b, &expected_result) != 3) {
        printf("strcmp test failed: unexpected end of file or incorrect format\n");
        return false;
    }

    int got_result = alt_strcmp(str_a, str_b);
    if (sign(got_result) != sign(expected_result)) {
        printf("strcmp test failed: expected result %d got result %d\n", expected_result, got_result);
        printf("on test: str_a=%s str_b=%s res=%d\n", str_a, str_b, expected_result);
        return false;
    }

    return true;
}

bool runStrchrTest(FILE* file){
    char str[100] = {'\0'};
    char chr = '\0';
    int expected_result = 0;

    if ( fscanf(file, " strchr %s C%c %d", str, &chr, &expected_result) != 3) {
        printf("strchr test failed: unexpected end of file or incorrect format\n");
        return false;
    }


    char* got_result_ptr = alt_strchr(str, chr);
    int got_result = -1;

    if (got_result_ptr != nullptr) {
        got_result = got_result_ptr - str;
    }

    if (sign(got_result) != sign(expected_result)) {
        printf("strchr test failed: expected result %d got result %d\n", expected_result, got_result);
        printf("on test: str=%s chr=%c res=%d\n", str, chr, expected_result);
        return false;
    }
    return true;
}

bool runSplitTest(FILE* file){
    char str[100] = {'\0'};
    size_t expected_nlines = 0;
    char separator = 0;

    if ( fscanf(file, " split %s S%c %d", str, &separator, &expected_nlines) != 3) {
        printf("split test failed: unexpected end of file or incorrect format\n");
        return false;
    }

    size_t got_nlines = 0;
    String* res = split( {str, strlen(str)}, &got_nlines, separator);

    if (expected_nlines == got_nlines) {
        printf("Comparing lines: ");
        bool test_passed = true;
        for (size_t i = 0; i < expected_nlines; i++) {
            char line[100] = {'\0'};
            fscanf(file, " %s", line);

            if (strcmp(line, res[i].chars) != 0) {
                printf("line  %d: Expected %s got %s   ", i, line, res[i].chars);
                test_passed = false;
            }
        }

        if (test_passed) {
            printf(" ...test passed\n");
            return true;
        }
        printf(" ...test failed\n");

    }
    else {
        printf("Test failed!\n");
        printf("Expected %d lines: ", expected_nlines);
        for (size_t i = 0; i < expected_nlines; i++) {
            char line[100] = {'\0'};
            fscanf(file, " %s", line);
            printf("%s ", line);
        }
        printf("\nGot %d lines: ", got_nlines);
        for (size_t i = 0; i < got_nlines; i++) {
            printf("%s ", res[i].chars);
        }
        printf("\n");
    }

    return false;
}

bool checkOnTestsFromFile(FILE* file, bool (*test_function)(FILE*)){
    int ntests = 0;
    if (fscanf(file, "ntests %d", &ntests) != 1) {
        printf("Can not read number of tests from file\n");
        return false;
    }

    bool all_tests_passed = true;
    for (int i = 0; i < ntests; i++) {
        if (!test_function(file)) {
            all_tests_passed = false;
        }
    }

    return all_tests_passed;
}

bool openAndCheckOnTestsFromFile(char* filename, bool (*test_function)(FILE*)) {
    FILE* file = fopen(filename, "r");
    if (file == nullptr) {
        printf("Error while opening file %s \n", filename);
        return false;
    }

    printf("\nRunning tests from file %s \n", filename);
    bool res = checkOnTestsFromFile(file, test_function);
    fclose(file);

    if (res)
        printf("Tests from file %s : passed\n", filename);
    else
        printf("Tests from file %s : errored\n", filename);

    return res;
}

int main(){
    openAndCheckOnTestsFromFile(".\\test_files\\strlen_tests.txt", runStrlenTest);
    openAndCheckOnTestsFromFile(".\\test_files\\strcpy_tests.txt", runStrcpyTest);
    openAndCheckOnTestsFromFile(".\\test_files\\strcat_tests.txt", runStrcatTest);
    openAndCheckOnTestsFromFile(".\\test_files\\strcmp_tests.txt", runStrcmpTest);
    openAndCheckOnTestsFromFile(".\\test_files\\strchr_tests.txt", runStrchrTest);
    openAndCheckOnTestsFromFile(".\\test_files\\split_tests.txt" , runSplitTest );
}

