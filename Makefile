CC = gcc
CFLAGS = -Winvalid-pch
PCH = /home/james/c/macros/vargc.h types.h macros.h generic.h
OPTFLAGS =
HEADER_FILES = $(wildcard *.h)
GCH = $(patsubst %.h,%.h.gch,$(HEADER_FILES))

all: jarr

jarr: jarr.c $(GCH)
	$(CC) $(OPTFLAGS) $(CFLAGS) -include $(PCH) -o $@ jarr.c

%.h.gch: %.h
	$(CC) $(OPTFLAGS) $(CFLAGS) -MMD -MF $(patsubst %.h.gch,%.d,$@) -MT $@ -o $@ -c $<

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
