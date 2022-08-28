#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <assert.h>

#include "file_read.h"
#include "msort.h"
#include "main.h"

int sort_cmp_norm   ( const void* ap, const void* bp) { sortComp( Strcmp  ) }
int sort_cmp_rtl    ( const void* ap, const void* bp) { sortComp( Strcmpe ) }
int sort_cmp_inv    ( const void* ap, const void* bp) { sortComp(-Strcmp  ) }
int sort_cmp_inv_rtl( const void* ap, const void* bp) { sortComp(-Strcmpe ) }

const char * const HELP_STRING = "Reads all lines from input file, sorts them and puts to standard output\n"
                                 "Options: \n"
                                 "-file [filename]        : used to specify input file. Default name is \"input.txt\" \n"
                                 "--invert-sorting        : inverts sorting order. \n"
                                 "--rtl-sorting           : compares lines right-to-left instead of left-to-right."
                                                          " (makes last characters most significant in sorting) \n"
                                 "--remove-leading-spaces : removes all leading spaces from lines. \n"
                                 "--shakespeare-mode      : removes lines NOT startig with ' ';"
                                                          " removes all lines starting with \"Enter\", \"Exit\", \"Re-enter\" and \"Exeunt\";"
                                                          " Works best with --remove-leading-spaces; Was created to support format of \"Hamlet\" \n"
                                 "--help                  : display this text\n";

int main(int argc, const char* argv[]) {
    const char* filename = "input.txt";

    int arg_filename = parseArg(argc, argv, "--file");
    if ( (arg_filename != ARG_NOT_FOUND) && (arg_filename + 1 < argc)) {
        filename = argv[arg_filename + 1];
    }

    bool invert_sort_mode      = parseArg(argc, argv, "--invert-sorting"          ) != ARG_NOT_FOUND;
    bool right_to_left_mode    = parseArg(argc, argv, "--rtl-sorting"             ) != ARG_NOT_FOUND;
    bool shakespeare_mode      = parseArg(argc, argv, "--shakespeare-mode"        ) != ARG_NOT_FOUND;
    bool remove_leading_spaces = parseArg(argc, argv, "--remove-leading-spaces"   ) != ARG_NOT_FOUND;

    if (parseArg(argc, argv, "--help") != ARG_NOT_FOUND) {
        printf(HELP_STRING);
        return 0;
    }


    int (*comparators[2][2] )(const void*, const void*) =
    {{sort_cmp_norm, sort_cmp_rtl    },
     {sort_cmp_inv , sort_cmp_inv_rtl}};

    FILE* input = fopen (filename, "r");

    if (input == nullptr) {
        fprintf(stderr, "File Not Found\n");
        return 0;
    }

    errno = 0;
    String file_content = readFile(input);
    if (file_content.chars == nullptr) {
        perror("Error while reading file");
        return EXIT_FAILURE;
    }

    int line_count = 0;
    errno = 0;
    String* lines = split(file_content, &line_count, '\n');
    if (lines  == nullptr) {
        perror("Unexpected error");
        return EXIT_FAILURE;
    }

    fclose(input);
    for (int i = 0; i < line_count; i++){
        if (*(lines[i].chars) != ' ' && shakespeare_mode) {
            *(lines[i].chars) = '\0';
            lines[i].length = 0;
        }

        if (remove_leading_spaces)
        lstrip(&lines[i], ' ');

        if (isEnterExit(lines[i].chars) && shakespeare_mode) {
            *(lines[i].chars) = '\0';
            lines[i].length = 0;
        }
    }

    msort(lines, line_count, sizeof(String), comparators[invert_sort_mode][right_to_left_mode] );

    for (int i = 0; i < line_count; i++) {
        if (lines[i].length != 0) {
            printf("%s\n", lines[i].chars);
        }
    }

    free(file_content.chars);
    free(lines);
    return 0;
}

int parseArg(int argc, const char* argv[], const char* arg_to_find) {
    for (int x = 1; x < argc; x++) { //i
        if (strcmp(argv[x], arg_to_find) == 0){
            return x;
        }
    }
    return ARG_NOT_FOUND;
}

bool isEnterExit(const char* a) {
    while ((*a) == ' ') a++;

    return ( (strncmp(a, "Enter", 5) == 0) || (strncmp(a, "Exit", 4) == 0) || (strncmp(a, "Exeunt", 6) == 0) ||  (strncmp(a, "Re-enter", 8) == 0) );
}
