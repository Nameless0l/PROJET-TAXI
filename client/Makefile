CC=gcc
CFLAGS=-m64
LDFLAGS=-m64

EXEC=./bin/client.out

all: $(EXEC)

$(EXEC): main.o client.o
	$(CC) -o $(EXEC) $^ $(LDFLAGS)

main.o: src/main.c
	$(CC) -c $< $(CFLAGS)

client.o: src/client.c
	$(CC) -c $< $(CFLAGS)

clean:
	rm *.o

mrproper:
	rm -f $(EXEC)

launch:
	$(EXEC)