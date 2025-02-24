#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include "../LogError/Log.h"

FILE *openFile(const char * const fileName, const char * const mode)
{
    assert(fileName && mode);

    FILE *file = fopen(fileName, mode);
    if (file == nullptr)
        LogError("File: %s wasn`t openned", fileName);       

    return file;
}

char *readFile(FILE *file)
{
    assert(file);

    char *code = nullptr;
    ssize_t fileSize = GetFileSize(file);
    if (fileSize <= 0)
    {   
        LogError("FSFDS");
        return nullptr;
    }

    char *buffer = (char *) calloc(fileSize, sizeof(char));
    if (buffer == nullptr)
    {
        LogError("mem");
        return buffer;
    }

    if (fread(buffer, sizeof(char), fileSize, file) != fileSize)
        LogError("fuck bill gates(done)");

    return buffer;

    
}

char *readFileByName(const char * const fileName)
{
    assert(fileName);

    ssize_t fileSize = GetFileSizeByName(fileName);
    if (fileSize <= 0)
    {
        LogError("helhel");
        return nullptr;
    }
    char *buffer = (char *) calloc(fileSize, sizeof(char));
    if (buffer == nullptr)
    {
        LogError("mem");
        return buffer;
    }

    FILE *file = openFile(fileName, "rb");

    if (fread(buffer, sizeof(char), fileSize, file) != fileSize)
        LogError("fuck bill gates(done)");

    return buffer;
}

ssize_t GetFileSizeByName(const char * const fileName)
{
    assert(fileName);

    struct _stat fileInfo = {};

    if (_stat(fileName, &fileInfo) != 0)
    {    
        LogError("FIle:dsa");
        return 0;
    }

    return fileInfo.st_size;
}

ssize_t GetFileSize(FILE *file)
{
    assert(file);

    struct _stat fileInfo = {};
    int fileDescriptor = _fileno(file);
    if (fileDescriptor == -1)
    {
        LogError("get file size");
        return 0;
    }

    if (_fstat(fileDescriptor, &fileInfo) != 0)
    {
        LogError("hellhe");
        return 0;
    }

    return fileInfo.st_size;
}

const char *NewStringAdr(const char *string)
{
    assert(string);

    while (*string != '\0')
    {
        if (*string == '\n')
            return (string + 1); 

        string++;
    }

    return nullptr;
}