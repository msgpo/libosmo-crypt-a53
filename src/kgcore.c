/*---------------------------------------------------------
 *              KGCORE
 *---------------------------------------------------------
 *
 * A sample implementation of KGCORE, the heart of the
 * A5/3 algorithm set.
 *
 * This has been coded for clarity, not necessarily for
 * efficiency.
 *
 * This will compile and run correctly on both Intel
 * (little endian) and Sparc (big endian) machines.
 *
 * Version 0.1      13 March 2002
 *
 *---------------------------------------------------------*/
#include "kasumi.h"
#include <stdio.h>
#include <stdint.h>

/*---------------------------------------------------------
 * KGcore()
 *      Given ca, cb, cc, cd, ck, cl generate c0
 *---------------------------------------------------------*/
void KGcore( u8 ca, u8 cb, u32 cc, u8 cd, u8 *ck, u8 *co, int cl )
{
     REGISTER64 A;        /* the modifier         */
     REGISTER64 temp;     /* The working register */
     int i, n;
     u8 key[16],ModKey[16];       /* Modified key     */
     u16 blkcnt;          /* The block counter */
     /* Copy over the key */
     for( i=0; i<16; ++i )
         key[i] = ck[i];
     /* Start by building our global modifier */
     temp.b32[0]   = temp.b32[1]  = 0;
     A.b32[0]      = A.b32[1]     = 0;
     /* initialise register in an endian correct manner*/
     A.b8[0] = (u8)   (cc>>24);
     A.b8[1] = (u8)   (cc>>16);
     A.b8[2] = (u8)   (cc>>8);
     A.b8[3] = (u8)   (cc);
     A.b8[4] = (u8)   (cb<<3);
     A.b8[4] |= (u8)  (cd<<2);
     A.b8[5] = (u8)   ca;
     /* Construct the modified key and then "kasumi" A */
     for( n=0; n<16; ++n )
         ModKey[n] = (u8)(ck[n] ^ 0x55);
     KeySchedule( ModKey );
     Kasumi( A.b8 ); /* First encryption to create modifier */
     /* Final initialisation steps */
     blkcnt = 0;
     KeySchedule( key );
     /* Now run the key stream generator */
    while( cl > 0 )
    {
        /* First we calculate the next 64-bits of keystream */
        /* XOR in A and BLKCNT to last value */
        temp.b32[0] ^= A.b32[0];
        temp.b32[1] ^= A.b32[1];
        temp.b8[7] ^= blkcnt;
        /* KASUMI it to produce the next block of keystream */
        Kasumi( temp.b8 );
        /* Set <n> to the number of bytes of input data *
         * we have to modify. (=8 if length <= 64)      */
        if( cl >= 64 )
             n = 8;
        else
             n = (cl+7)/8;
        /* copy out the keystream */
        for( i=0; i<n; ++i )
             *co++ = temp.b8[i];
        cl -= 64;        /* done another 64 bits */
        ++blkcnt;        /* increment BLKCNT */
    }
}
/*-----------------------------------------------------------
 *          e n d    o f    K G c o r e . c
 *-----------------------------------------------------------*/
