CC = gcc
CFLAGS = -Wall -I/usr/include/postgresql -L/usr/lib/x86_64-linux-gnu -lpq
BIN_DIR = /home/karaulnyi/bin

all: printer

connect_printer.o: connect_printer.c printer.h
	$(CC) -c connect_printer.c -o connect_printer.o $(CFLAGS)

add_printer.o: add_printer.c printer.h
	$(CC) -c add_printer.c -o add_printer.o $(CFLAGS)

get_printer.o: get_printer.c printer.h
	$(CC) -c get_printer.c -o get_printer.o $(CFLAGS)

printer.o: printer.c printer.h
	$(CC) -c printer.c -o printer.o $(CFLAGS)

printer: connect_printer.o add_printer.o get_printer.o printer.o
	$(CC) connect_printer.o add_printer.o get_printer.o printer.o -o printer $(CFLAGS)

install: printer
	mkdir -p $(BIN_DIR)
	cp printer $(BIN_DIR)/

clean:
	rm -f *.o printer
