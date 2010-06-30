
#include <stdint.h>

#include <osmocom/crypt/gprs_cipher.h>

#include "kasumi.h"
#include "a53f.h"

static int gea3_run(uint8_t *out, uint16_t len, uint64_t kc, uint32_t iv,
		     enum gprs_cipher_direction direction)
{
	uint8_t dir;

	if (direction == GPRS_CIPH_MS2SGSN)
		dir = 0;
	else
		dir = 1;

	GEA3((uint8_t *)&kc, sizeof(kc), iv, dir, out, len);

	return 0;
}

static struct gprs_cipher_impl gea3_impl = {
	.algo = GPRS_ALGO_GEA3,
	.name = "3GPP Reference implementation of GEA3",
	.priority = 1000,
	.run = &gea3_run,
};

static void __attribute__((constructor)) osmo_crypt_a5_init(void)
{
	gprs_cipher_register(&gea3_impl);

	/* FIXME: A5/3 registration */
}
