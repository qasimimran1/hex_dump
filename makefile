CC=gcc
CFLAGS=-Wall -g

# all:	dumper
dumper:	main.o dumper.o options.o
		gcc -o dumper dumper.o main.o options.o
build:	main.c dumper.c  options.c
		gcc -c main.c dumper.c options.c
clean:
	rm -f dumper dumper.o main.o options.o