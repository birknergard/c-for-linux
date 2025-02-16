#Makefile template

INCLDIR = ./include
CC = gcc
CFLAGS = -O2
CFLAGS += -I $(INCLDIR)
CFLAGs += -std=c89

OBJDIR = obj

_DEPS = source.h
DEPS = $(patsubst %,$(INCLDIR)/%,$(_DEPS))

_OBJS = o4.o
OBJS = $(patsubst %,$(OBJDIR)/%,$(_OBJS))

$(OBJDIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

o4: $(OBJS)
	gcc -o $@ $^ $(CFLAGS)

.PHONY: clean
clean:
	rm -f $(OBJDIR)/*.o *~ core $(INCLDIR)/*~



