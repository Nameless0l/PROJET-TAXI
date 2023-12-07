
all:
# compiling modules
	cd ./OC && make
	cd ./UI && make
	cd ./RPG && make
	cd ./bike && make
	cd ./client && make

clean:
	cd ./UI && make clean
	cd ./OC && make clean
	cd ./RPG && make clean
	cd ./bike && make clean
	cd ./client && make clean