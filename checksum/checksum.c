/*
 * Tool to calculate 16-bit (big endian) checksums for Mega Drive ROMs.
 * C99 compliant.
 */

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>

struct args {
	const char *progname;
	const char *romfile;
	int validargs;
	bool apply;
	bool print;
} args;

int main(int argc, char *argv[])
{
	/* Declarations */
	FILE *romfile;
	uint16_t checksum, word;

	/* Initialize argument values */
	args.progname = NULL;
	args.romfile = NULL;
	args.validargs = 0;
	args.apply = false;
	args.print = false;

	/* Get program filename */
	args.progname = argv[0];
	for (int i = 0; argv[0][i] != '\0'; i++) {
		if ((argv[0][i] == '\\') || (argv[0][i] == '/'))
			args.progname = &argv[0][i + 1];
	}

	/* If no arguments, print usage string */
	if (argc == 1) {
		printf("USAGE:\n"
			"\t\"%s [ROM] [options]\"\n"
			"\tOR\n"
			"\t\"%s [options] [ROM]\"\n"
			"\n"
			"OPTIONS:\n"
			"\t-a\tApply calculated checksum to ROM header.\n"
			"\t-p\tPrint calculated checksum.\n",
			args.progname, args.progname);
		exit(1);
	}
	
	/* Parse remaining arguments */
	for (int i = 1; i < argc; i++) {
		bool unknown = false;
		if (argv[i][0] == '-') {
			switch (argv[i][1]) {
			case 'a':
			case 'A':
				if (argv[i][2] == '\0') {
					args.apply = true;
					args.validargs++;
				} else {
					unknown = true;
				}
				break;
			
			case 'p':
			case 'P':
				if (argv[i][2] == '\0') {
					args.print = true;
					args.validargs++;
				} else {
					unknown = true;
				}
				break;

			default:
				unknown = true;
			}
		} else if (args.romfile == NULL) {
			args.romfile = argv[i];
		} else {
			unknown = true;
		}
		if (unknown)
			printf("%s: Ignoring unknown argument \"%s\".\n", args.progname, argv[i]);
	}

	/* Test requested file */
	if (args.romfile == NULL) {
		printf("%s: No ROM file specified.\n", args.progname);
		exit(1);
	} else if (args.validargs == 0) {
		printf("%s: No operations given for ROM file. Defaulting to printing checksum...\n", args.progname);
		args.print = true;
	}
	
	/* Open requested file */
	if (!(romfile = fopen(args.romfile, "rb+"))) {
		printf("%s: Cannot open file \"%s\".\n", args.progname, args.romfile);
		exit(1);
	}

	/* Main loop */
	fseek(romfile, 0x200, SEEK_SET);
	checksum = 0;
	for (int i = 0; feof(romfile) == 0; i++) {
		if ((i & 1) == 0) {
			// Odd (low byte, big endian)
			word = (0 | (fgetc(romfile) << 8));
		} else {
			// Even (high byte, big endian)
			word |= fgetc(romfile);
			checksum += word;
		}
	}

	/* Report checksum */
	if (args.print == true)
		printf("%s: Checksum calculated for this ROM is: %d (0x%04X).\n", args.progname, checksum, checksum);

	/* Apply checksum */
	if (args.apply == true) {
		fseek(romfile, 0x18E, SEEK_SET);
		fputc((unsigned char)(checksum >> 8), romfile);
		fputc((unsigned char)checksum, romfile);
	}

	/* Quit */
	fclose(romfile);
	return 0;
}
