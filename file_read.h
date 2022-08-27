#ifndef FILE_READ_H_INCLUDED
#define FILE_READ_H_INCLUDED
#include "String.h"

//! gets size of file (number of characters in it)
//! @param [in] file input file
//! @return size
//! @note returns 0 in case of error
int getFileSize( FILE* file);

//! reads file as string
//! @param [in] file input file
//! @param [out] file_size size of file
//! @return file content as string
//! @note function allocates memory for its output. You need to free() it
//! @note returns nullptr in case of error
String readFile( FILE* file);



#endif
