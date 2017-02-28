CC=gcc
CFLAGS = -Wall -std=c99

all:main

main:
	$(CC) $(CFLAGS) avltree.c -o avltree
