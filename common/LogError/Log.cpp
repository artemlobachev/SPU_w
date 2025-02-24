#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
//#include <execinfo.h>

#include "Log.h"
#include "Error.h"
#include "UsefulPrints.h"

int LOG_DESCRIPTOR = 0xDEAD;

static LogErrors LogMeme()
{
    static const ssize_t MEME_SIZE = 1024;

    
    static char MemeBuffer[MEME_SIZE] = MEME;

    ssize_t WriteBytes = write(LOG_DESCRIPTOR, MemeBuffer, MEME_SIZE);
    if (WriteBytes <= 0)
    {
        fprintf(stderr, "Log file write error: %s\n Write %llu bytes max size = %llu", strerror(errno), WriteBytes, MEME_SIZE);

        return (WriteBytes == 0) ? LogErrors::EOF_ERROR : LogErrors::FILE_WRITE_ERROR;
    }

    return LogErrors::NO_ERROR;
}

static LogErrors LogEnd()
{
    LogMeme();
    //write(LOG_DESCRIPTOR, ,sizeof(LOG_DESCRIPTOR));

    if (close(LOG_DESCRIPTOR) == -1)
    {
        perror("Error closing log file");
        return LogErrors::LOG_CLOSE_ERROR;
    }
    LOG_DESCRIPTOR = 0XDEAD;

    return LogErrors::NO_ERROR;
}

static LogErrors OpenLogDescriptor(const char *LogFileName) 
{
    assert(LogFileName);

    static const char *FileFormat = ".log.html";
    static const ssize_t MAX_FILE_NAME_SIZE = 256;
    static char FileNameBuffer[MAX_FILE_NAME_SIZE] = "";

    assert(strlen(LogFileName) + strlen(FileFormat) <= MAX_FILE_NAME_SIZE);
    snprintf(FileNameBuffer, MAX_FILE_NAME_SIZE, "%s%s", LogFileName, FileFormat);

    LOG_DESCRIPTOR = open(FileNameBuffer, O_WRONLY | O_CREAT);
    if (LOG_DESCRIPTOR == -1)
    {
        fprintf(stderr, "Log file open error: %s\n", strerror(errno));
        return LogErrors::OPEN_DESCRIP_ERROR;
    }

    return LogErrors::NO_ERROR;
}

LogErrors LogOpen(const char *LogFileName)
{
    assert(LogFileName);

    OpenLogDescriptor(LogFileName);

    //LogBegin();

    if (atexit(LogClose))
        return LogErrors::LOG_CLOSE_ERROR;

    return LogErrors::NO_ERROR;
}

const char *SetHeadByLvl(enum LogLevel lvl)
{
    switch(lvl)
    {
        case LOG_INFO:
            return HEAD_INFO; 

        case LOG_WARNING:
            return HEAD_WARNING;

        case LOG_ERROR:
            return HEAD_ERROR;
        
        default:
            return nullptr;
    };
}

LogErrors LogByLvl(enum LogLevel lvl, const char *message, ...)
{
    assert(message);

    va_list args = {};
    va_start(args, message);

    static const ssize_t MAX_LOG_SIZE = 1024;
    static char LogBuffer[MAX_LOG_SIZE] = "";
    vsnprintf(LogBuffer, MAX_LOG_SIZE, message, args);

    va_end(args);

    const char *HEAD = SetHeadByLvl(lvl); 
    if (HEAD == nullptr)
    {
        COLOR_PUTS(RED, "UNDEFINED COMMAND");
        return LogErrors::
    }

    int err1 = write(LOG_DESCRIPTOR, HEAD, sizeof(HEAD));
    int err2 = write(LOG_DESCRIPTOR, LogBuffer, MAX_LOG_SIZE);
    int err3 = write(LOG_DESCRIPTOR, HEAD_END, sizeof(HEAD_END));

    if (err1 ==  0 || err2 ==  0 || err3 == 0)
    {
        perror("EOF while write: ");
        return LogErrors::EOF_ERROR;
    }    

    if (err1 == -1 || err2 == -1 || err3 == -1)
    {
        perror("Write in file by descriptor error: ");
        return LogErrors::FILE_WRITE_ERROR;
    }

    return LogErrors::NO_ERROR;
}