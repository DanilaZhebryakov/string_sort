//! @file String.h
//! contains String struct and some helper functions

#ifndef STRING_H_INCLUDED
#define STRING_H_INCLUDED

//! structure which stores string and its length as int
struct String{
    char* chars;
    int length;
};

//! version of strcmp which compares strings right-to-left instead of left-to-right and uses String* as input
int Strcmpe(const String* a, const String* b);

//! version of strcmp which uses String* as input
int Strcmp (const String* a, const String* b);

//! removes all target_char characters from beginning of string (WARNING: function moves the beginning of string. Be careful if using free())
//! @param str pointer to input string
//! @param target_char character to remove
//! @return number of character removed
int lstrip(String* str, char target_char);

//! splits string by given separator character and outputs it as array of strings
//! @param [in] str input_string
//! @note this function changes input_string (replaces all separators with '\0's)
//! @param [in] file_size size of input string
//! @param [out] nlines size of the output array
//! @param [in] separator separator character to split string by
//! @return parts of input string as array of strings
//! @note function allocates memory for its output. You need to free() it
//! @note returns nullptr in case of error
String* split(String str, int* file_size, char separator);

//! counts '\n' terminated lines (+ 1 for '\0' terminated) in given string
//! @param [in] str input string
//! @return number of lines
//! @note returns 0 in case of error
int countLines(char* str);


#endif // STRING_H_INCLUDED
