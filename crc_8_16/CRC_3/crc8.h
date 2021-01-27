unsigned char crc8_compute(unsigned char init, const unsigned char *data, int count);
unsigned char crc8_single(unsigned char a, unsigned char b);
void crc8_generate_table(unsigned char poly);
