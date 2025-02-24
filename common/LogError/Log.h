#ifndef LOG_H
#define LOG_H

#include "UsefulPrints.h"

#define MEME "<blockquote style = \"color: greenyellow\">                                             \
		        \"Самое трудное в жизни - засунуть одеяло в пододеяльник\" - Джейсон Стетхем           \
	          </blockquote>" 

enum class LogErrors
{
    NO_ERROR,
    OPEN_DESCRIP_ERROR,
    LOG_CLOSE_ERROR,
    EOF_ERROR,
    FILE_WRITE_ERROR
};

enum LogLevel
{
    LOG_INFO,
    LOG_WARNING,
    LOG_ERROR
};

LogErrors LogOpen     (const char *LogFileName);
LogErrors Log         (const char *message, ...);
LogErrors LogError(const char *ErrorMessage, ...);

#endif