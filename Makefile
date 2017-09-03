INCLUDE=./include
CFLAGS=-Wall -std=c11 -O -I$(INCLUDE) -c
EXE=main
SRCFILES=main.c args.c fs_util.c join.c remove.c
TESTFILES=fs_util_test.c
CC=gcc
OBJS=$(SRCFILES:.c=.o)
TOBJS=$(TESTFILES:.c=.o)

all: $(EXE)


$(EXE): $(OBJS)
	$(CC) -o $(EXE) $(OBJS)

.c.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf *o main
