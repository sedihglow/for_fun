BIN = ../bin/d20.out
CC = gcc
CCFLAGS = -I ../include -c -Wall -Wextra
CCFLAGS+= -m64 -O0 -g -pedantic
LDFLAGS =
RUNARGS = --verbose --add -c argc -b optargs1 optargs2
VAL_ARGS = --leak-check=full

SRCS=$(wildcard ./*.c)
OBJS=$(SRCS:.c=.o)

OBJS_TO_CLEAN = $(BIN) ./$(OBJS)

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
						valgrind $(VAL_ARGS) $(BIN)

.PHONY: gdb
debug:					# GNU debugger
						$(info -- Debugging --)
						gdb $(BIN)

.PHONY: clean
clean:					# clean the directory
						$(info -- Cleaning The Directory --)
						rm -rf $(OBJS_TO_CLEAN)
.PHONY: run
run:					# run the program as follows
						$(info -- Running Program --)
						make
						$(BIN) $(RUNARGS)
