#Makefile template

TARGET = multiclient
LIBRARY = ../bexam_lib/bexamlib.a
INCLDIR = ./include
CC = gcc
CFLAGS = -O2
CFLAGS += -I $(INCLDIR)
CFLAGS += -std=c99
CFLAGS += -Wall
CFLAGS += -lpthread

OBJDIR = obj

_DEPS = $(TARGET).h
DEPS = $(patsubst %,$(INCLDIR)/%,$(_DEPS))

_OBJS = $(TARGET).o 
OBJS = $(patsubst %,$(OBJDIR)/%,$(_OBJS))

$(OBJDIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

$(TARGET): $(OBJS)
	gcc -o $@ $^ $(CFLAGS) $(LIBRARY)

.PHONY: clean
clean:
	rm -f $(OBJDIR)/*.o *~ core $(INCLDIR)/*~



