# BIKE PROJECT

The Taxi project is an operating system project that aims to develop a customer transportation algorithm by motorcycle taxis. The algorithm must respect a certain policy for selecting customers to transport, as well as the order of priority of requests. The algorithm must also be capable of optimizing the use of available resources, while simulating the natural operation of a motorcycle in reality. The operation of a motorcycle in reality includes the behavior and characteristics of a real motorcycle, such as: looking for a customer when the motorcycle is empty, going to a given destination when the motorcycle has a customer, etc.

The Taxi project falls within the domain of transportation, particularly for motorcycle taxi providers. It is indeed about guaranteeing customer satisfaction by offering them fast and reliable transportation. However, customer transportation poses a challenge, as it requires effectively managing a multitude of parameters, such as customer location, motorcycle availability, and delivery times.

## Features

The Taxi project is divided into four main modules, which are:

- **The Random Process Generator (RPG)**: This is a tool that simulates the behavior of customers and motorcycles in a real environment. It generates transport requests for motorcycles and customers at random intervals, reproducing the unpredictable patterns of human behavior.
- **The client module**: This is the module that represents the customers who request transportation. It generates customer information, such as their starting point, destination, price, and waiting time. It creates a shared memory segment, in which it writes its information. It sends a signal to the central scheduler (CS) to indicate that it has completed the initial part of the execution. It waits for a signal from the CS, which continues until it reaches its limit. If the allotted time is exceeded, the process is terminated, it sends a signal to the CS, and it is removed from the list of clients. It receives a signal from the motorcycle that informs it that it has been picked up. At the end of the trip, it receives a signal from the motorcycle indicating the end of the trip, and it terminates.
- **The motorcycle module**: This is the module that represents the motorcycles that provide transportation to customers. It generates the motorcycle's route, which is an array of neighborhoods, elements of an enumeration of all the neighborhoods in the city. It creates a shared memory segment, in which it writes its route. It sends a signal to the CS to indicate that it has completed the initial part of the execution. It waits for a signal from the CS, which reads the list of clients stored in the shared memory segment and selects the first client on the list, according to the FIFO policy. It receives a signal from the CS that assigns it a client to serve. It sends a signal to the client to inform it that it has been picked up. It sends a signal to the CS to indicate the transport of a client. It sends a signal to the client to indicate the end of the trip. It restarts the process from the beginning.
- **The central scheduler (CS)**: This is the module that coordinates communication between motorcycles and customers. It initializes two lists, one for clients and one for motorcycles. It listens to the various signals from motorcycles and clients for a given time. After this time, it masks the signals sent from now on for subsequent operations. It saves the various clients in the list using the FIFO policy, and it does the same for the various motorcycles. It assigns clients to available motorcycles, using the first-come, first-served protocol. It sends a signal to the chosen motorcycle and removes the chosen client from the list of clients. It restarts the process from the listening period and adds the masked elements to the appropriate lists.



## Getting Started

These instructions will get you a copy of the project up and running on your local
machine for development and testing purposes.

### Prerequisites

This project is meant to be only a template, thus versions of the software used
can be change to better suit the needs of the developer(s). If you wish to use the
template *as-is*, meaning using the versions recommended here, then you will need:

* **Make v4.2+**
```bash
sudo apt update
sudo apt install make
```

* **C Compiler** - needs to support at least the **C++17** standard, i.e. *MSVC*,
*GCC*, *Clang*. We recommand **GCC**
```bash
sudo apt update
sudo apt install gcc
```


* **GLibC_2.34** - check it with 
```bash 
ldd --version
```

* **Glut & OpenGL* - You need to install them for the UI
```bash
sudo apt-get install libglu1-mesa-dev freeglut3-dev mesa-common-dev
```
### Installing

It is fairly easy to install the project, all you need to do is clone if from
[GitHub](https://github.com/Nameless0l/PROJET-TAXI.git)
or you can download it with [this link](https://github.com/Nameless0l/PROJET-TAXI/archive/refs/head/main.zip)

If you wish to clone the repository, rather than generate from it, you simply need
to run: (Assuming that you have *GIT* installed)

```bash
git clone https://github.com/Nameless0l/PROJET-TAXI.git
```


## Building and executing the project

To build the project, all you need to do, ***after correctly
[installing the project](README.md#Installing)***, is run a similar **MAKE** routine
You have to follow the following steps:


* **Clean the previous commpilation**:
```bash
make clean 
``` 

* **Compile the project**:
```bash
make
```

* **Launch the UI**: Launch the UI and copy it **PID** displayed on the terminal. Also copy the pid of the OC after launching it
```bash
./UI/bin/ui.out <ui_pid>
```

Open another terminal another terminal to launch the OC

* **Launch the OC**:
```bash
./OC/bin/oc.out <ui_pid>
```

After launching the OC, you have to get it PID that will be logged in the terminal and then launch the RPG with it as args

* **Launch the RPG**:Open another terminal at the root of the project and type these command
```bash
./RPG/bin/rpg.out <oc_pid>
```


## Authors

* **Loic Ewolo Mbassi** - [@Nameless0l](https://github.com/Nameless0l)
* **Pacome Kengali Fegue** - [@PacomeKFP](https://github.com/PacomeKFP)
* **Igor Green Mogou** - [@IgorGreenIGM](https://github.com/IgorGreenIGM)
* **Pacifique Nganta** - [@PacomeKFP](https://github.com/PacomeKFP)
* **Jordan Vuide** - [@PacomeKFP](https://github.com/PacomeKFP)
* **Nina Laissa Ntye** - [@PacomeKFP](https://github.com/PacomeKFP)
* **Anne Rosalie Ngo Bassom** - [@PacomeKFP](https://github.com/PacomeKFP)
* **Gabriel Nomo** - [@NOMO-Gabriel](https://github.com/NOMO-Gabriel)

## License

This project is licensed under the [Unlicense](https://unlicense.org/) - see the
[LICENSE](LICENSE) file for details

