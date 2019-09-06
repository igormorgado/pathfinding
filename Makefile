OPTIONS=-std=c11 -pedantic -Werror -Wall -W \
  -Wmissing-prototypes -Wstrict-prototypes \
  -Wconversion -Wshadow -Wpointer-arith \
  -Wcast-qual -Wcast-align \
  -Wwrite-strings -Wnested-externs \
  -fshort-enums -fno-common -Dinline= -g -O2

all: io main
	gcc $(OPTIONS) io.o main.o -o main -lgsl

io:
	gcc $(OPTIONS) -g -O -c io.c

main:
	gcc $(OPTIONS) -g -O -c main.c


clean:
	rm -rf *.o main
