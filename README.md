# libexpression
A C++ library to express (and evaluate) symbolic equations

# System dependencies
clang-tidy
```bash
sudo apt install clang-tidy
```

## Building the project
The `libexpression` project's buils system is CMake based. In order to build it from source, run the following commands from your command line:
```bash
git clone --recurse-submodules https://github.com/fairlight1337/libexpression.git
cd libexpression
mkdir build
cd build
cmake ..
make
```
The resulting binary executables will then be in `build/bin`. After building, run the main executable with:
```bash
./bin/libexpression-bin
```
