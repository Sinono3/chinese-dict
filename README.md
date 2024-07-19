# Chinese Dictionary

This repository contains the source code for a Chinese dictionary app.
The GUI is built using FLTK.

## Dependencies

- FLTK 1.3
- C++20

### Linux/MacOS

Install the respective development FLTK package available in your distribution.
In MacOS you can install FLTK using `brew install fltk`.

Then you must clone the repository and run make:

```
$ git clone https://github.com/Sinono3/chinese-dict
$ cd chinese-dict
$ make run
```

The app should compile and run after these steps.

### Windows

You need to install [MSYS2](https://www.msys2.org/) and download the 64-bit UCRT MinGW toolchain and FLTK with it.
You can do so by typing this in the MSYS2 UCRT64 terminal:

```
$ pacman -S base-devel mingw-w64-ucrt-x86_64-toolchain mingw-w64-ucrt-x86_64-fltk
```

After this simply run `make run` inside the terminal and inside the project directory and the game should compile and run.

### Windows (Visual Studio)

If you instead want to compile this using Visual Studio, you will have to create a project in Visual Studio and manually configure includes and linking for FLTK.
