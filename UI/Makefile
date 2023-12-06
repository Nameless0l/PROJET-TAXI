### __MAKEFILE___ ###

CC=gcc
CFLAGS=-m64 -lGL -lGLU -lglut -lm
LDFLAGS=-m64 -lGL -lGLU -lglut -lm

EXEC=./bin/oc.out

all: $(EXEC)

$(EXEC): main.o draws.o list.o ui.o handler.o
	$(CC) -o $(EXEC) $^ $(LDFLAGS)

main.o: src/main.c
	$(CC) -c $< $(CFLAGS)

draws.o: src/draws.c
	$(CC) -c $< $(CFLAGS)

list.o: src/list.c
	$(CC) -c $< $(CFLAGS)

ui.o: src/ui.c
	$(CC) -c $< $(CFLAGS)

handler.o: src/handler.c
	$(CC) -c $< $(CFLAG)
	
clean:
	rm -f *.o

launch:
	$(EXEC)