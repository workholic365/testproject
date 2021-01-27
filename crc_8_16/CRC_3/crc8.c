#include "crc8.h"

static unsigned char crctab[8];

/*
 * Generates an unsigned char table with 8 entries.
 */
void crc8_generate_table(unsigned char poly)
{
	int i;
	unsigned char residue = poly;

	for (i=0;i<8;i++) {
		int carry;

		crctab[i] = residue;
		carry = residue & 0x80;
		residue <<= 1;
		if (carry)
			residue ^= poly;
	}
}

/*
 * Single iteration of a the CRC computation
 */
unsigned char crc8_single(unsigned char a, unsigned char b)
{
	unsigned char *residue = crctab;

	while (b) {
		if (b & 1)
			a ^= *residue;
		b >>= 1;
		residue++;
	}

	return a;
}

/*
 * Compute CRC8 of a string
 */
unsigned char crc8_compute(unsigned char init, const unsigned char *data, int count)
{
	unsigned char crc = init;

	while (count--) {
		crc = crc8_single(*data, crc);
		data++;
	}

	return crc;
}
