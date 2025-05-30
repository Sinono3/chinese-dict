# Chinese Dictionary

This repository contains the source code for a Chinese dictionary app.
The GUI is built using FLTK.

## Dependencies

- FLTK 1.3
- C++20

## Explanation

#### `src/main.cpp`

Contains the main function and all the UI logic.

#### `src/DictionaryEntry.hpp`/`src/DictionaryEntry.cpp`

Defines the `DictionaryEntry` struct.

#### `src/csv.hpp`/`src/csv.cpp`

Contains functions for loading and saving to CSV files.

#### `src/search.hpp`/`src/search.cpp`

Contains the function to search in the entries.
Also defines the `SearchResult` struct.

#### `src/pinyin/*.hpp`/`src/pinyin/*.cpp`

Contains the following enums/structs/classes:

- Tone: Enum representing the five tones in Pinyin.
- Consonant: Enum representing a consonant.
- ConsonantStr: A consonant and a string.
- Vowel: Enum representing 1-3 vowels.
- VowelStr: A vowel and a string.
- Syllable: A consonant, a vowel and a tone.
- PrettySyllable: Wrapper for Syllable. Output operator overloaded to pretty print the syllable.
- PrettyWord: Wrapper for Word. Output operator overloaded to pretty print the syllable.

Also some type definitions:

- PinyinWord = `std::vector<Syllable>`

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
