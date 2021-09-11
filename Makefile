OBJNAME=slscq
CC=g++
SRCDIR=cpp_ver
CFLAGS=-I $(SRCDIR)/include

$(OBJNAME): $(SRCDIR)/main.cpp
	$(CC) $(CFLAGS) $< -o $@
