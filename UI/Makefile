
make:
# compiling modules
	rm -rf *.o
	cd ../OC && make 
	cd ../moto && make
	cd ../client && make
	cd ../RPG && make 

clean:
	cd ../OC && make clean
	cd ../moto && make clean
	cd ../client && make clean
	cd ../RPG && make clean

launch_oc:
	cd ./OC && make launch 

launch:
	cd ./RPG && make launch $(ARGS)