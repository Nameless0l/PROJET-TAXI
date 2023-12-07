CC=gcc
CFLAGS=-m64
LDFLAGS=-m64

EXEC=./bin/bike.out

all: $(EXEC)

$(EXEC): main.o initialisation-bikes.o signal.o
	$(CC) -o $(EXEC) $^ $(LDFLAGS)

main.o: src/main.c	
	$(CC) -c $< $(CFLAGS)

initialisation-bikes.o: src/initialisation-bikes.c
	$(CC) -c $< $(CFLAGS)

signal.o: src/signal.c
	$(CC) -c $< $(CFLAGS)

clean:
	rm *.o

mrproper:
	rm -f $(EXEC)

launch:
	$(EXEC)