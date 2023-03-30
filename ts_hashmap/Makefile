all: main.c ts_hashmap.o parseInputs.o rtclock.o
	gcc -Wall -g -o hashtest main.c ts_hashmap.o parseInputs.o rtclock.o -lpthread

ts_hashmap.o: ts_hashmap.h ts_hashmap.c
	gcc -Wall -g -c ts_hashmap.c

parseInputs.o: parseInputs.c
	gcc -Wall -g -c parseInputs.c
	
rtclock.o: rtclock.h rtclock.c
	gcc -Wall -g -c rtclock.c

clean:
	rm -f hashtest *.o

