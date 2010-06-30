#ifndef A53_F_H
#define A53_F_H

void GSM( u8 *key, int klen, int count, u8 *block1, u8 *block2 );
void ECSD( u8 *key, int klen, int count, u8 *block1, u8 *block2 );
void GEA3( u8 *key, int klen, u32 input, u8 direction, u8 *block, int m );

#endif
