CC=gcc
FLAGS_DEV=-Wall -Wextra -pedantic -Ofast

.PHONY: clean fork datetime
default: fork

wrapper.o: common/wrapper.c
	$(CC) -c common/wrapper.c $(FLAGS_DEV)

forkserver.o: fork/forkserver.c
	$(CC) -c fork/forkserver.c $(FLAGS_DEV)

forkclient.o: fork/forkclient.c
	$(CC) -c fork/forkclient.c $(FLAGS_DEV)

fork: forkserver.o forkclient.o wrapper.o
	mkdir -p build/
	$(CC) wrapper.o forkserver.o -o forkserver $(FLAGS_DEV)
	$(CC) wrapper.o forkclient.o -o forkclient $(FLAGS_DEV)
	mv forkserver forkclient build/
	rm -rf *.o

datetime: datetime.c wrapper.o

clean:
	rm -rf build
