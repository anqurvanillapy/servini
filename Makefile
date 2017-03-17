CC=gcc
FLAGS_DEV=-Wall -Wextra -pedantic -Ofast

.PHONY: clean forks http10
default: forks http10

wrapper.o: common/wrapper.c
	$(CC) -c common/wrapper.c $(FLAGS_DEV)

forkgets.o: fork/forkgets.c
	$(CC) -c fork/forkgets.c $(FLAGS_DEV)

forkputs.o: fork/forkputs.c
	$(CC) -c fork/forkputs.c $(FLAGS_DEV)

forks: forkgets.o forkputs.o wrapper.o
	mkdir -p build/
	$(CC) wrapper.o forkgets.o -o forkgets $(FLAGS_DEV)
	$(CC) wrapper.o forkputs.o -o forkputs $(FLAGS_DEV)
	mv forkgets forkputs build/

forkhttp10.o: fork/forkhttp10.c
	$(CC) -c fork/forkhttp10.c $(FLAGS_DEV)

http10: forkhttp10.o wrapper.o
	mkdir -p build/
	$(CC) wrapper.o forkhttp10.o -o forkhttp10 $(FLAGS_DEV)
	mv forkhttp10 build/

clean:
	rm -rf build
	rm -rf *.o
