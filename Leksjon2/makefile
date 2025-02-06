#
# Generic makefile for compiling and linking more than one source file
#

OBJS = hello.o number.o # List object files here
# DEPS = number.h
CFLAGS = -O2

%.o: %.c $(DEPS)
	gcc -c -o $@ $< $(CFLAGS)

hello: $(OBJS)
	gcc -o $@ $^ $(CFLAGS)

.phony: clean
clean:
	rm -f *.o

