CCFLAGS := -Wall -O3
LDFLAGS := -static

all: 4bppto1bpp checksum

4bppto1bpp: 4bppto1bpp.c
	cc $(CCFLAGS) -o $@ $^ $(LDFLAGS)

checksum: checksum.c
	cc $(CCFLAGS) -o $@ $^ $(LDFLAGS)

# dependency rules
4bppto1bpp.c: common.h
checksum.c: common.h

.PHONY: clean
clean:
	rm -rf 4bppto1bpp checksum
