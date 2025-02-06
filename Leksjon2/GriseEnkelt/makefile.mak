#
# Simple makefile for compiling and linking one single source file
#

TARGET = griseenkelt

$(TARGET) : $(TARGET).c
	gcc -O2 $^ -o $@


