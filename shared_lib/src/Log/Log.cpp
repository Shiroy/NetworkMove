#include "Log.h"
#include <stdarg.h>
#include <stdio.h>

Log::Log()
{

}

Log::~Log()
{

}

void Log::Error(const char *msg, ...)
{
    if(!msg)
        return;

    va_list ap;
    va_start(ap, msg);
    char nString[32*1024];
    vsprintf(nString, msg, ap);

    std::string putMsg("[ERREUR] ");
    putMsg += nString;
    putMsg += "\n";
    std::cout << putMsg;
    va_end(ap);
}

void Log::Message(const char *msg, ...)
{
    if(!msg)
        return;

    va_list ap;
    va_start(ap, msg);
    char nString[32*1024];
    vsprintf(nString, msg, ap);

    std::string putMsg = "[LOG] ";
    putMsg += nString;
    putMsg += "\n";
    std::cout << putMsg;
}

void Log::Print(const char *msg, ...)
{
    if(!msg)
        return;

    va_list ap;
    va_start(ap, msg);
    char nString[32*1024];
    vsprintf(nString, msg, ap);

    std::string putMsg = nString;
    putMsg += "\n";
    std::cout << putMsg;
}

void Log::Debug(const char *msg, ...)
{
    if(!msg)
        return;

    va_list ap;
    va_start(ap, msg);
    char nString[32*1024];
    vsprintf(nString, msg, ap);

    std::string putMsg = "[DEBUG] ";
    putMsg += nString;
    putMsg += "\n";
    std::cout << putMsg;
}
