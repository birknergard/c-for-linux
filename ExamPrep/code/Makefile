#Makefile template

INCLDIR = ./include
CC = gcc
CFLAGS = -O2
CFLAGS += -I $(INCLDIR)
# -lsocket, -lsockets (for server)
CFLAGS += -std=c89
CFLAGS += -Wpedantic
CFLAGS += -Wall

OBJDIR = obj

_DEPS = debug.h server.h 
DEPS = $(patsubst %,$(INCLDIR)/%,$(_DEPS))

_OBJS =  debug.o server.o
OBJS = $(patsubst %,$(OBJDIR)/%,$(_OBJS))

$(OBJDIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

main: $(OBJS)
	gcc -o $@ $^ $(CFLAGS)

.PHONY: clean
clean:
	rm -f $(OBJDIR)/*.o *~ core $(INCLDIR)/*~



