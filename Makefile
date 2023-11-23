
make:
	cd ./OC && make 
	cd ./moto && make
	cd ./client && make
	cd ./RPG && make rpg_bike
	cd ./RPG && make rpg_client

clean:
	cd ./OC && make clean
	cd ./moto && make clean
	cd ./client && make clean
	cd ./RPG && make clean

launch_oc:
	cd ./OC && make launch 

launch:
	cd ./RPG && make launch $(ARGS)