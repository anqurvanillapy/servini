CC=gcc
FLAGS_DEV=-Wall -Wextra -pedantic -Ofast

.PHONY: clean
default: build

socket.o: servini/socket.c
	$(CC) -c servini/socket.c $(FLAGS_DEV)

wrapper.o: servini/common/wrapper.c
	$(CC) -c servini/common/wrapper.c $(FLAGS_DEV)

build: socket.o wrapper.o
	mkdir -p build
	$(CC) socket.o wrapper.o $(FLAGS_DEV)
	mv a.out build/

clean:
	rm -rf build *.o
