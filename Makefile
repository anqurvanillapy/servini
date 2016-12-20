CC=gcc

.PHONY: clean
default: build

socket.o: servini/socket.c
	$(CC) -c servini/socket.c

wrapper.o: servini/common/wrapper.c
	$(CC) -c servini/common/wrapper.c

build: socket.o wrapper.o
	mkdir -p build
	$(CC) socket.o wrapper.o
	mv a.out build/

clean:
	rm -rf build *.o
