/*---------------------------------------------------------
 *              A5/3
 *---------------------------------------------------------
 *
 * A sample implementation of A5/3, the functions of the
 * A5/3 algorithm set.
 *
 * This has been coded for clarity, not necessarily for
 * efficiency.
 *
 * This will compile and run correctly on both Intel
 * (little endian) and Sparc (big endian) machines.
 *
 * Version 0.1       13 March 2002
 *
 *---------------------------------------------------------*/
#include "kasumi.h"
#include <stdlib.h>
void KGcore( u8 ca, u8 cb, u32 cc, u8 cd, u8 *ck, u8 *co, int cl );

/*---------------------------------------------------------
  * BuildKey()
  * The KGcore() function expects a 128-bit key. This
  * function builds that key from shorter length keys.
  *---------------------------------------------------------*/
static u8 *BuildKey( u8 *k, int len )
{
     static u8 ck[16];          /* Where the key is built */
     int i, n, sf;
     u8 mask[]={0x1,0x3,0x7,0xF,0x1F,0x3F,0x7F,0xFF};
     i = (len+7)/8;             /* Round to nearest byte  */
     if (i > 16 )
          i = 16;               /* limit to 128 bits      */
     for( n=0; n<i; ++n )       /* copy over the key      */
          ck[n] = k[n];
     sf = len%8;                /* Any odd key length?    */
     /* If the key is less than 128-bits we need to replicate *
       * it as many times as is necessary to fill the key.     */
     if( len < 128 )
     {
          n = 0;
          if( sf )      /* Doesn't align to byte boundaries */
          {
               ck[i-1] &= mask[sf];
               ck[i-1] += ck[0]<<sf;
               while( i<16 )
               {
                   ck[i] = (ck[n]>>(8-sf)) + (ck[n+1]<<sf);
                   ++n;
                   ++i;
               }
          }
          else
               while( i<16 )
                   ck[i++] = ck[n++];
     }
     return( ck );
}

/*---------------------------------------------------------
 * The basic A5/3 functions.
 * These follow a standard layout:
 * - From the supplied key build the 128-bit required by
 *    KGcore()
 * - Call the KGcora() function with te appropriate
 *    parameters
 * - Take the generated Keystream and repackage it
 *    in the required format.
 */
/*---------------------------------------------------------
 * The standard GSM function
 *---------------------------------------------------------*/
void GSM( u8 *key, int klen, int count, u8 *block1, u8 *block2 )
{
     u8 *ck, data[32];
     int i;
     ck=BuildKey( key, klen );
     KGcore( 0x0F, 0, count, 0, ck, data, 228 );
     for( i=0; i<15; ++i )
     {
         block1[i] = data[i];
         block2[i] = (data[i+14]<<2) + (data[i+15]>>6);
     }
     block1[14] &= 0xC0;
     block2[14] &= 0xC0;
}

/*---------------------------------------------------------
  * The standard GSM ECSD function
  *---------------------------------------------------------*/
void ECSD( u8 *key, int klen, int count, u8 *block1, u8 *block2 )
{
     u8 *ck, data[87];
     int i;
     ck=BuildKey( key, klen );
     KGcore( 0xF0, 0, count, 0, ck, data, 696 );
     for( i=0; i<44; ++i )
     {
         block1[i] = data[i];
         block2[i] = (data[i+43]<<4) + (data[i+44]>>4);
     }
     block1[43] &= 0xF0;
     block2[43] &= 0xF0;
}

/*---------------------------------------------------------
 * The standard GEA3 function
 *---------------------------------------------------------*/
void GEA3( u8 *key, int klen, u32 input, u8 direction, u8 *block, int m )
{
     u8 *ck, *data;
     int i;
     data = malloc( m );
     ck=BuildKey( key, klen );
     KGcore( 0xFF, 0, input, direction, ck, data, m*8 );
     for( i=0; i<m; ++i )
         block[i] = data[i];
     free( data );
}

/*---------------------------------------------------------
 * E n d o f A 5 3 f . c
 *---------------------------------------------------------*/

