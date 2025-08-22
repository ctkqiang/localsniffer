CC=gcc
CFLAGS=-Wall -Iinclude
LDFLAGS=-lpcap

SRC=src/capture.c src/logger.c src/parser.c src/utilities.c localsniffer.c
OBJ=$(SRC:.c=.o)

sniff: $(OBJ)
	$(CC) -o $@ $(OBJ) $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f src/*.o localsniffer.o sniff
