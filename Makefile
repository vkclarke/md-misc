# edit this line to specify a desired compiler
CC = cc

CCFLAGS := -Wall -O3
LDFLAGS := -static

all: 4bppto1bpp checksum

4bppto1bpp: 4bppto1bpp.c
	$(CC) $(CCFLAGS) -o $@ $^ $(LDFLAGS)

checksum: checksum.c
	$(CC) $(CCFLAGS) -o $@ $^ $(LDFLAGS)

# dependency rules
4bppto1bpp.c: headers
checksum.c: headers

.PHONY: headers
headers: common.h fixedint.h

.PHONY: clean
clean:
	rm -rf 4bppto1bpp checksum
