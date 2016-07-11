#ifndef A53_F_H
#define A53_F_H

void GSM( u8 *key, int klen, int count, u8 *block1, u8 *block2 )  __attribute__((__deprecated__("Deprectaed: use implementation from libosmogsm instead")));
void ECSD( u8 *key, int klen, int count, u8 *block1, u8 *block2 );
void GEA3( u8 *key, int klen, u32 input, u8 direction, u8 *block, int m ) __attribute__((__deprecated__("Deprectaed: use implementation from libosmogsm instead")));

#endif
