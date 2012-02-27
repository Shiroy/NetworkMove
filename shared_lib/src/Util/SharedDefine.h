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