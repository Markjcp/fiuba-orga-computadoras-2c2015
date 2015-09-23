CC = gcc
CFLAGS = -c -Wall -I src/
PROG = autcel
DEFAULT = generic
SRC = src/

c_plotter: $(SRC)plotter.c $(SRC)plotter.h $(SRC)proximo.S
	$(CC) $(CFLAGS) $(SRC)plotter.c
	
c_main: $(SRC)main.c $(SRC)plotter.h
	$(CC) $(CFLAGS) $(SRC)main.c

as_proximo: $(SRC)proximo.S
	$(CC) $(CFLAGS) $(SRC)proximo.S
	
c_proximo: $(SRC)proximo.c
	$(CC) $(CFLAGS) $(SRC)proximo.c
	
mips: as_proximo c_plotter c_main
	$(CC) main.o plotter.o proximo.o -o $(PROG)

generic: c_proximo c_plotter c_main
	$(CC) main.o plotter.o proximo.o -o $(PROG)

	
clean:
	rm -rf *.o $(PROG)