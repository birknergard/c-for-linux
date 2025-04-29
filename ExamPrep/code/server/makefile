#Makefile template
TARGET = server_2 
LIBRARY = ../bexam_lib/bexamlib.a
INCLDIR = ./include
CC = gcc
CFLAGS = -O2
CFLAGS += -I $(INCLDIR)
CFLAGS += -std=c99
CFLAGS += -Wall
CFLAGS += -lpthread

OBJDIR = obj

_DEPS = $(addsuffix .h, $(TARGET))
DEPS = $(patsubst %,$(INCLDIR)/%,$(_DEPS))

_OBJS = $(addsuffix .o, $(TARGET))
OBJS = $(patsubst %,$(OBJDIR)/%,$(_OBJS))

$(OBJDIR)/%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

$(TARGET): $(OBJS)
	gcc -o $@ $^ $(CFLAGS) $(LIBRARY)

.PHONY: clean
clean:
	rm -f $(OBJDIR)/*.o *~ core $(INCLDIR)/*~



