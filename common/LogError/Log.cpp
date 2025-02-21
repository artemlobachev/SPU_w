#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
//#include <dbghelp.h>

#include "Log.h"
#include "Error.h"
#include "UsefulPrints.h"

int LOG_DESCRIPTOR;

static LogErrors LogMeme()
{
    static const ssize_t MEME_SIZE = 1024;

   // CaptureStackBackTrace();

    static char MemeBuffer[MEME_SIZE] = MEME;

    int error = write(LOG_DESCRIPTOR, MemeBuffer, MEME_SIZE);
    if (error == 0)
    {
        perror("EOF while write: ");

        return LogErrors::EOF_ERROR;
    }
    if (error == -1)
    {
        perror("Write in file by descriptor error: ");

        return LogErrors::FILE_WRITE_ERROR;
    }

    return LogErrors::NO_ERROR;
}

static LogErrors LogBegin(const char *BeginBlock)
{
    assert(BeginBlock);

    //Stack;
}

static LogErrors LogEnd()
{
    LogMeme();
    //write(LOG_DESCRIPTOR, ,sizeof());

    close(LOG_DESCRIPTOR);
    LOG_DESCRIPTOR = 0XDEAD;
}

void LogClose()
{


    close(LOG_DESCRIPTOR);
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
        perror("Log file open error: ");
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

LogErrors Log(const char *message, ...)
{
    assert(message);

    va_list args = {};
    va_start(args, message);

    static const ssize_t MAX_LOG_SIZE = 1024;
    static char LogBuffer[MAX_LOG_SIZE] = "";
    vsprintf(LogBuffer, message, args);

    va_end(args);

    int err1 = write(LOG_DESCRIPTOR, HEAD_WHITE, sizeof(HEAD_WHITE));
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

LogErrors LogError(const char *ErrorMessage, ...)
{
    assert(ErrorMessage);

    va_list args = {};
    va_start(args, ErrorMessage);

    static const ssize_t MAX_LOG_SIZE = 1024;
    static char LogBuffer[MAX_LOG_SIZE] = "";
    vsprintf(LogBuffer, ErrorMessage, args);

    va_end(args);

    int err1 = write(LOG_DESCRIPTOR, HEAD_RED, sizeof(HEAD_WHITE));
    int err2 = write(LOG_DESCRIPTOR, LogBuffer, MAX_LOG_SIZE);
    int err3 = write(LOG_DESCRIPTOR, HEAD_END, sizeof(HEAD_END));

    if (err1 ==  0 || err2 ==  0 || err3 == 0) // 0 - EOF
    {
        perror("EOF while write: ");
        return LogErrors::EOF_ERROR;
    }
    if (err1 == -1 || err2 == -1 || err3 == -1) // wasn`t writted by descriptor
    {
        perror("Write in file by descriptor error: ");
        return LogErrors::FILE_WRITE_ERROR;
    }

    return LogErrors::NO_ERROR;
}
