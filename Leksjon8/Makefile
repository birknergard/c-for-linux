#Makefile template

INCLDIR = ./include
CC = gcc
CFLAGS = -O2
CFLAGS += -I $(INCLDIR)
CFLAGS += -lpthread
CFLAGS += -std=c89

OBJDIR = obj

_DEPS = default.h
DEPS = $(patsubst %,$(INCLDIR)/%,$(_DEPS))

_OBJS = o3.o
OBJS = $(patsubst %,$(OBJDIR)/%,$(_OBJS))

$(OBJDIR)/%.o: %.c $(DEPS) 
	$(CC) -c -o $@ $< $(CFLAGS)

o3: $(OBJS)
	gcc -o $@ $^ $(CFLAGS)

.PHONY: clean
clean:
	rm -f $(OBJDIR)/*.o *~ core $(INCLDIR)/*~



