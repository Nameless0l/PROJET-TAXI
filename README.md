# BIKE PROJECT

An academic Project

## Features

* Modern **CMake** configuration and project, which, to the best of my
knowledge, uses the best practices,

* An example of a **Clang-Format** config, inspired from the base *Google* model,
with minor tweaks. This is aimed only as a starting point, as coding style
is a subjective matter, everyone is free to either delete it (for the *LLVM*
default) or supply their own alternative,


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
make clean_ui
``` 

* **Compile the project**:
```bash
make
make build_ui
```

* **Launch the UI**: Launch the UI and copy it **PID** displayed on the terminal. Also copy the pid of the OC after launching it
```bash
make launch_ui
```

Open another terminal another terminal to launch the OC

* **Launch the OC**:
```bash
cd ./OC
./bin/oc.out <ui_pid>
```

After launching the OC, you have to get it PID that will be logged in the terminal and then launch the RPG with it as args

* **Launch the RPG**:Open another terminal at the root of the project and type these command
```bash
cd ./RPG
./bin/rpg.out <oc_pid>
```

### End to end tests





## Authors

* **Loic Ewolo Mbassi** - [@Nameless0l](https://github.com/Nameless0l)
* **Pacome Kengali Fegue** - [@PacomeKFP](https://github.com/PacomeKFP)
* **Igor Green Mogou** - [@IgorGreenIGM](https://github.com/IgorGreenIGM)
* **Pacifique Nganta** - [@PacomeKFP](https://github.com/PacomeKFP)
* **Jordan Vuide** - [@PacomeKFP](https://github.com/PacomeKFP)
* **Nina Laissa Ntye** - [@PacomeKFP](https://github.com/PacomeKFP)
* **Anne Rosalie Ngo Bassom** - [@PacomeKFP](https://github.com/PacomeKFP)
* **Gabriel Nassaire** - [@PacomeKFP](https://github.com/PacomeKFP)

## License

This project is licensed under the [Unlicense](https://unlicense.org/) - see the
[LICENSE](LICENSE) file for details

