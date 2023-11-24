CC=gcc
CFLAGS=-m64
LDFLAGS=-m64

EXEC=./bin/rpg.out

all: $(EXEC)

$(EXEC): rpg.o
	$(CC) -o $(EXEC) $^ $(LDFLAGS)

rpg.o: src/rpg.c
	$(CC) -c $< $(CFLAGS)

clean:
	rm *.o

mrproper:
	rm -f $(EXEC)

launch:
	$(EXEC)