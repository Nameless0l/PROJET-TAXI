
make:
# compiling modules
	cd ./OC && make 
	cd ./moto && make
	cd ./client && make
	cd ./RPG && make 

clean:
	cd ./OC && make clean
	cd ./moto && make clean
	cd ./client && make clean
	cd ./RPG && make clean

clean_ui:
	cd ./UI && make clean

build_ui:
	cd ./UI && make 

launch_ui:
	cd ./UI && make launch 

launch_oc:
	cd ./OC && make launch 

launch:
	cd ./RPG && make launch $(ARGS)