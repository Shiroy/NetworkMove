/*
NetworkMove : un projet de MMORPG éducatif
Copyright (C) 2012  Antoine Wacheux (Eryldor) and the NetworkMove development team

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

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
