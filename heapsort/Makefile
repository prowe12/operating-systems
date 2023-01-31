
#all: tests.c heap.h employee.h heap.o
#	gcc -Wall -g -o tests main.c heap.o
#
#all: main.c heap.h employee.h heap.o
#	gcc -Wall -g -o heapsort main.c heap.o

all: heapsort tests

heapsort: main.c
	gcc -Wall -g -o heapsort main.c heap.o

tests: tests.c
	gcc -Wall -g -o tests tests.c heap.o

heap.o: heap.h heap.c
	gcc -Wall -g -c heap.c
clean:
	rm -f heapsort *.o
