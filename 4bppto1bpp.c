#include <stdio.h>

#include "fixedint.h"

/*
 * Lookup table for converting "duxels" (single byte containing two 4-bit pixels)
 * to two-bit (1-bit per pixel) values. These can be shifted left when applying
 * to a 1bpp pixel row depending on the horizontal position of the duxel.
 */
static const u8 duxel_lut[256] = {
	0b00, 0b01, 0b01, 0b01, 0b01, 0b01, 0b01, 0b01,
	0b01, 0b01, 0b01, 0b01, 0b01, 0b01, 0b01, 0b01,
	0b10, 0b11, 0b11, 0b11, 0b11, 0b11, 0b11, 0b11,
	0b11, 0b11, 0b11, 0b11, 0b11, 0b11, 0b11, 0b11,
	0b10, 0b11, 0b11, 0b11, 0b11, 0b11, 0b11, 0b11,
	0b11, 0b11, 0b11, 0b11, 0b11, 0b11, 0b11, 0b11,
	0b10, 0b11, 0b11, 0b11, 0b11, 0b11, 0b11, 0b11,
	0b11, 0b11, 0b11, 0b11, 0b11, 0b11, 0b11, 0b11,
	0b10, 0b11, 0b11, 0b11, 0b11, 0b11, 0b11, 0b11,
	0b11, 0b11, 0b11, 0b11, 0b11, 0b11, 0b11, 0b11,
	0b10, 0b11, 0b11, 0b11, 0b11, 0b11, 0b11, 0b11,
	0b11, 0b11, 0b11, 0b11, 0b11, 0b11, 0b11, 0b11,
	0b10, 0b11, 0b11, 0b11, 0b11, 0b11, 0b11, 0b11,
	0b11, 0b11, 0b11, 0b11, 0b11, 0b11, 0b11, 0b11,
	0b10, 0b11, 0b11, 0b11, 0b11, 0b11, 0b11, 0b11,
	0b11, 0b11, 0b11, 0b11, 0b11, 0b11, 0b11, 0b11,
	0b10, 0b11, 0b11, 0b11, 0b11, 0b11, 0b11, 0b11,
	0b11, 0b11, 0b11, 0b11, 0b11, 0b11, 0b11, 0b11,
	0b10, 0b11, 0b11, 0b11, 0b11, 0b11, 0b11, 0b11,
	0b11, 0b11, 0b11, 0b11, 0b11, 0b11, 0b11, 0b11,
	0b10, 0b11, 0b11, 0b11, 0b11, 0b11, 0b11, 0b11,
	0b11, 0b11, 0b11, 0b11, 0b11, 0b11, 0b11, 0b11,
	0b10, 0b11, 0b11, 0b11, 0b11, 0b11, 0b11, 0b11,
	0b11, 0b11, 0b11, 0b11, 0b11, 0b11, 0b11, 0b11,
	0b10, 0b11, 0b11, 0b11, 0b11, 0b11, 0b11, 0b11,
	0b11, 0b11, 0b11, 0b11, 0b11, 0b11, 0b11, 0b11,
	0b10, 0b11, 0b11, 0b11, 0b11, 0b11, 0b11, 0b11,
	0b11, 0b11, 0b11, 0b11, 0b11, 0b11, 0b11, 0b11,
	0b10, 0b11, 0b11, 0b11, 0b11, 0b11, 0b11, 0b11,
	0b11, 0b11, 0b11, 0b11, 0b11, 0b11, 0b11, 0b11,
	0b10, 0b11, 0b11, 0b11, 0b11, 0b11, 0b11, 0b11,
	0b11, 0b11, 0b11, 0b11, 0b11, 0b11, 0b11, 0b11
};

int main(int argc, char *argv[])
{
	/* Declarations */
	FILE *in, *out;
	int i;
	unsigned char c1, c2;

	if (argc == 1) {
		printf("No arguments entered.\n");
		return -1;
	}

	if (argc == 2) {
		printf("Too few arguments to function.\n");
		return -1;
	}

	if ((in = fopen(argv[1], "rb")) == NULL) {
		printf("Cannot open input file \"%s\".\n", argv[1]);
		return -1;
	}

	if ((out = fopen(argv[2], "w")) == NULL) {
		printf("Cannot create output file \"%s\".\n", argv[2]);
		fclose(in);
		return -1;
	}

	/* Main loop */
	for (i = 3; feof(in) == 0; i = ((i - 1) & 3)) {
		c1 = fgetc(in);

		if (i == 3)
			c2 = (duxel_lut[c1] << (i * 2));
		else
			c2 |= (duxel_lut[c1] << (i * 2));

		if (i == 0)
			fputc(c2, out);
	}

	fclose(in);
	fclose(out);
	return 0;
}
