CC=gcc
FILES=main.c lib/extclib.o

.PHONY: default build run
default: build run

build: $(FILES)
	$(CC) -o main $(FILES) 
run: main
	./main
