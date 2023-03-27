CC = gcc
CFLAGS = -Winvalid-pch
PCH = /home/james/c/pp_macros/pp_va_args_macros.h types.h macros.h generic.h
OPTFLAGS =
HEADER_FILES = $(wildcard *.h)
GCH = $(patsubst %.h,%.h.gch,$(HEADER_FILES))

all: t

t: t.c $(GCH)
	$(CC) $(OPTFLAGS) $(CFLAGS) -include $(PCH) -o $@ t.c

%.h.gch: %.h
	$(CC) $(OPTFLAGS) $(CFLAGS) -MMD -MF $(patsubst %.h.gch,%.d,$@) -MT $@ -o $@ -c $<

.PHONY: clean clean-gch rebuild

clean:
	-@rm -f t

clean-gch:
	-@rm -f $(GCH)

rebuild: clean-gch clean all
