#ifndef KASUMI_H
#define KASUMI_H

#include <stdint.h>

/*---------------------------------------------------------
 *                  Kasumi.h
 *---------------------------------------------------------*/
typedef unsigned char     u8;
typedef unsigned short   u16;
typedef unsigned   int   u32;

/*----- a 64-bit structure to help with endian issues -----*/
typedef union {
    u32 b32[2];
    u16 b16[4];
    u8 b8[8];
} REGISTER64;

/*------------- prototypes --------------------------------*/
void KeySchedule( u8 *key );
void Kasumi( u8 *data );

#endif /* KASUMI_H */
