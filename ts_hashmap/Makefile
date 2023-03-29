all: main.c ts_hashmap.o parseInputs.o
	gcc -Wall -g -o hashtest main.c ts_hashmap.o parseInputs.o -lpthread

ts_hashmap.o: ts_hashmap.h ts_hashmap.c
	gcc -Wall -g -c ts_hashmap.c

parseInputs.o: parseInputs.c
	gcc -Wall -g -c parseInputs.c
clean:
	rm -f hashtest *.o
