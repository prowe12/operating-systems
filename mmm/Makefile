all: main.c mmm.o parseInputs.o rtclock.o
	gcc -O3 -Wall -g -o mmm main.c mmm.o parseInputs.o rtclock.o -lpthread -lm

mmm.o: mmm.h mmm.c
	gcc -Wall -g -c mmm.c

parseInputs.o: parseInputs.h parseInputs.c
	gcc -Wall -g -c parseInputs.c

rtclock.o: rtclock.h rtclock.c
	gcc -Wall -g -c rtclock.c

clean:
	rm -f mmm *.o
