CC = gcc
CFLAGS = -Wall -Wextra -Wpedantic

all: myprogram

myprogram: myprogram.c
	$(CC) $(CFLAGS) -o $@ $<

clean:
	rm -f myprogram