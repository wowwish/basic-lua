
## Steps to run Code

```
make build
./main
```

Use `make clean` to remove precompiled binary `main` and recompile the binaryusing `make build`. Also, since Lua scripts used in C are loosely coupled, you don't have to recreate the binary when you modify the Lua scripts used in the C program.

# SDL Installation

Simple Directmedia Layer (SDL) is a library in C that provides abstractions of the hardware layer for use within C. SDL takes care of communicating between C and the keyboard inputs, mouse, graphics display driver etc and supports multiple OS including windows, linux, MacOS, Android etc. The wrapper APIs available in SDL are common across multiple OS platforms and it abstracts away the low-level details of communicating with the hardware using the available OS capabilities. 

To install SDL:

For Linux

```
sudo apt-get install libsdl2-dev
```

For MacOS

```
brew install sdl2
```

For windows, download installer of SLD version 2.0 from the [SDL Website](https://www.libsdl.org)

__NOTE__: Once installed, the SDL library files have to be linked with the gcc compiler to successfully compile the code into executable binary. Hence, if you are using the SDL library in your code, then add `-lSDL2` to the GCC compiler when compiling the source code. Usually, most C libraries are linked
to the code when compiling with the GCC compiler using '-l<library_name>' 
