#include <stdio.h>
#include "crc8.h"

#define CRC_POLY 0x1d
#define CRC_INIT 0xb0

int main()
{
	unsigned char sample[8] = { 0x20, 0x00, 0x20, 0x0c, 0x04, 0xff, 0x00, 0x00 };
	unsigned char crc;

	/*
	 * It is easy to modify this for a fixed table, but I've opted for computing
	 * at initialization.
	 */
	crc8_generate_table(CRC_POLY);

	/*
	 * Two ways to compute CRC8:
	 * 1. Run crc8_compute on your sample and then do a single run with a 0
	 */
	crc = crc8_compute(CRC_INIT, sample, 7);
	crc = crc8_single(0, crc);
	printf ("CRC8 method 1: 0x%02x\n", crc);

	/*
	 * 2. Run crc8_compute on your sample, padded with a zero.
	 */
	crc = crc8_compute(CRC_INIT, sample, 8);
	printf ("CRC8 method 2: 0x%02x\n", crc);

	/*
	 * By replacing the last byte with the CRC, we form a valid packet. Checking
	 * that the packet is valid is easy. Run crc8_compute on it, and it should
	 * return 0.
	 */
	sample[7] = crc;
	printf ("Verify: 0x%02x\n", crc8_compute(CRC_INIT, sample, 8));
}
