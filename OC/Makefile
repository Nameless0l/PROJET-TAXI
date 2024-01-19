CC=gcc
CFLAGS=-m64 -lGL -lGLU -lglut -lm
LDFLAGS=-m64 -lGL -lGLU -lglut
CFLAGS = 
LDFLAGS = 

EXEC=./bin/oc.out

all: $(EXEC)

$(EXEC): main.o oc.o handlers.o list.o gData_list.o
	$(CC) -o $(EXEC) $^ $(LDFLAGS)

main.o: src/main.c
	$(CC) -c $< $(CFLAGS)

oc.o: src/oc.c
	$(CC) -c $< $(CFLAGS)

handlers.o: src/handlers.c
	$(CC) -c $< $(CFLAGS)

list.o: src/list.c
	$(CC) -c $< $(CFLAGS)

gData_list.o: src/gData_list.c
	$(CC) -c $< $(CFLAGS)

clean:
	rm *.o

mrproper:
	rm -f $(EXEC)

launch:
	$(EXEC)