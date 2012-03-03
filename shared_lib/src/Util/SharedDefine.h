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

#ifndef SHARED_H
#define SHARED_H

typedef double uint64;
typedef unsigned int uint32;
typedef unsigned short uint16;
typedef unsigned char uint8;

typedef double int64;
typedef int int32;
typedef short int16;
typedef char int8;

enum AUTH_RESPONSE
{
    AUTH_OK = 0x00,
    AUTH_WRONG_PASSWORD = 0x01,
    AUTH_BANNED = 0x02,
};

#undef NULL
#define NULL 0

#define IN_MILLISECOND 1000

#endif
