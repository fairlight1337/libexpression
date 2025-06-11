# libexpression
A C++ library to express (and evaluate) symbolic equations

## Building the project
The `libexpression` project's buils system is CMake based. In order to build it from source, run the following commands from your command line:
```bash
git clone https://github.com/fairlight1337/libexpression.git
cd libexpression
git submodule update --init --recursive
mkdir build
cd build
cmake ..
make
```
The project uses Catch2 for its unit tests. Catch2 is provided via a git submodule
and will only be available after running the submodule initialization step above.
The resulting binary executables will then be in `build/bin`. After building, run the main executable with:
```bash
./bin/libexpression-bin
```
