CC = gcc
CFLAGS  = -g -Wall -I src/
SRC = src/

default: autcel

autcel:  plotter.o main.o 
	$(CC) $(CFLAGS) -o autcel plotter.o main.o

plotter.o:  $(SRC)plotter.c $(SRC)plotter.h 
	$(CC) $(CFLAGS) -c $(SRC)plotter.c

main.o:  $(SRC)main.c $(SRC)plotter.h 
	$(CC) $(CFLAGS) -c $(SRC)main.c

clean: 
	$(RM) count *.o *~