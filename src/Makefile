BIN = ../bin/d20.out
CC = gcc
CCFLAGS = -I ../include -I -c -Wall -Wextra
CCFLAGS+= -m64 -O0 -g -pedantic -std=c99
LDFLAGS = -m64

SRCS=$(wildcard ./*.c)
OBJS=$(SRCS:.c=.o)

.PHONY: all
all: $(BIN)

$(BIN):$(OBJS)
						$(CC) $(OBJS) -o $@ $(LDFLAGS)

%.o:%.c
						$(CC) $(CCFLAGS) -o $@ -c $<

.PHONY: valgrind
valgrind:				# check for memory leak
						$(info -- Checking For Memory Leaks --)
						make
						valgrind --leak-check=full ../bin/d20.out

.PHONY: gdb
debug:					# GNU debugger
						$(info -- Debugging --)
						gdb ../bin/d20.out

.PHONY: clean
clean:					# clean the directory
						$(info -- Cleaning The Directory --)
						rm -rf ./$(OBJS) ../bin/d20.out
.PHONY: run
run:					# run the program as follows
						$(info -- Running Program --)
						make
						../bin/d20.out --verbose --add -c argc -b optargs1\
						optargs2
