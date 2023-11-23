CC=gcc
CFLAGS=-m64
LDFLAGS=-m64

EXEC_BIKE=./bin/rpg_bike.out
EXEC_CLIENT=./bin/rpg_client.out

rpg_bike: rpg_client.o
	$(CC) -o $(EXEC_CLIENT) rpg_client.o $(LDFLAGS)

rpg_client: rpg_bike.o
	$(CC) -o $(EXEC_BIKE) rpg_bike.o $(LDFLAGS)

rpg_client.o: src/rpg_client.c
	$(CC) -c $< $(CFLAGS)

rpg_bike.o: src/rpg_bike.c
	$(CC) -c $< $(CFLAGS)

all: 
	$(CC) -o $(EXEC_CLIENT) rpg_client.o $(LDFLAGS)
	$(CC) -o $(EXEC_BIKE) rpg_bike.o $(LDFLAGS)
compile_bike_rpg:
	$(CC) -o $(EXEC_BIKE) rpg_bike.o $(LDFLAGS)

clean:
	rm *.o

mrproper:
	rm -f $(EXEC)

launch:
	$(EXEC_CLIENT) $(ARGS)
	$(EXEC_BIKE) $(ARGS)

launch_rpg_client:
	$(EXEC_CLIENT) $(ARGS) &

launch_rpg_bike:
	$(EXEC_BIKE) $(ARGS) &