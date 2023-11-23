CC=gcc
CFLAGS=-m64
LDFLAGS=-m64

EXEC=./bin/oc.out

all: $(EXEC)

$(EXEC): main.o oc.o handlers.o deque.o
	$(CC) -o $(EXEC) $^ $(LDFLAGS)

main.o: src/main.c
	$(CC) -c $< $(CFLAGS)

oc.o: src/oc.c
	$(CC) -c $< $(CFLAGS)

handlers.o: src/handlers.c
	$(CC) -c $< $(CFLAGS)

deque.o: src/deque.c
	$(CC) -c $< $(CFLAGS)

clean:
	rm *.o

mrproper:
	rm -f $(EXEC)

launch:
	$(EXEC)