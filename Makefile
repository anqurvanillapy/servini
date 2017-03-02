CC=gcc
FLAGS_DEV=-Wall -Wextra -pedantic -Ofast

.PHONY: clean
default: fork

forkserver.o: fork/forkserver.c
	$(CC) -c fork/forkserver.c $(FLAGS_DEV)

wrapper.o: fork/common/wrapper.c
	$(CC) -c fork/common/wrapper.c $(FLAGS_DEV)

fork: forkserver.o wrapper.o
	mkdir -p build/
	$(CC) forkserver.o wrapper.o $(FLAGS_DEV)
	mv a.out build/

clean:
	rm -rf build *.o
