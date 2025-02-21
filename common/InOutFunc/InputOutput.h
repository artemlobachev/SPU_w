#ifndef IO_H
#define IO_H

#include <stdio.h>
#include <assert.h>
#include <sys/types.h>


enum class InOutError
{
    NO_ERROR,

};

ssize_t getFileSize      (FILE *file);
ssize_t getFileSizeByName(const char * const fileName);
FILE *openFile           (const char * const fileName, const char * const mode);
char *readFileByName     (const char * const fileName);
char *readFile           (FILE *file);
const char *NewStringAdr (const char *string);


#endif