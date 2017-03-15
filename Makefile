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

datetime.o: fork/datetime.c
	$(CC) -c fork/datetime.c $(FLAGS_DEV)

datetime: datetime.o wrapper.o
	mkdir -p build/
	$(CC) wrapper.o datetime.o -o datetime $(FLAGS_DEV)
	mv datetime build/
	rm -rf *.o

clean:
	rm -rf build
