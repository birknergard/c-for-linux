INCLDIR = ./include
CC = gcc
CFLAGS = -O0
CFLAGS += -I $(INCLDIR)

# Sets compiler standard to c89
CFLAGS += -std=c89
# Display all warnings
#CFLAGS += -Wall
# For creating just obj files library

OBJDIR = obj

_DEPS = debug.h menu.h util.h doubl_list.h 
DEPS = $(patsubst %,$(INCLDIR)/%,$(_DEPS))

_OBJS = debug.o menu.o util.o doubl_list.o  
OBJS = $(patsubst %,$(OBJDIR)/%,$(_OBJS))

$(OBJDIR)/%.o: %.c $(DEPS)
	$(CC) -o $@ $< $(CFLAGS) 

lib: $(OBJS)
	$(CC) -o -c $@ $^ $(CFLAGS)
	ar rcs bexamlib.a $(OBJS)

test:
	$(CC) test.c bexamlib.a $(CFLAGS) -o test  

.PHONY: clean
clean:
	rm -f $(OBJDIR)/*.o *~ core $(INCLDIR)/*~



