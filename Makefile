CC = gcc
CFLAGS = -std=c11
PCH = /home/james/c/macros/vargc.h types.h macros.h generic.h
OPTFLAGS =
GCH = $(patsubst %.h,%.h.gch,$(wildcard *.h))

all: jarr

jarr: jarr.c $(GCH)
	$(CC) $(OPTFLAGS) $(CFLAGS) -include $(PCH) -o $@ jarr.c

%.h.gch: %.h
	$(CC) $(OPTFLAGS) $(CFLAGS) -x c-header -o $@ $<

.PHONY: clean clean-gch rebuild

clean:
	-@rm -f jarr

clean-gch:
	-@rm -f $(GCH)

rebuild: clean-gch clean all

build.ninja: CMakeLists.txt
	cmake -GNinja -Bbuild

.PHONY: ninja
ninja: build.ninja
	ninja -C build
