# Brace Expansion Program
Brace expansion algorithm written in C++. Directory Structure:
* braceExpand.h, braceExpand.cpp: source files containing algorithm for expanding braces
* brace.m.cpp: The main executable that takes input and outputs the expanded string.
* braceExpand.t.cpp: Runs unit-tests from the testing spec.
* Makefile: for building the source and running.

## Build Instructions
The source can be built using the provided Makefile.
To build all the files (including unit tests):

`make`

That, should produce two executables:
1. *brace.out*: The main program that accepts input from the user
2. *test.out*: Runs the testing suite

## How to build manually?
Building the main program:

`g++ -o brace.out brace.m.cpp braceExpand.cpp -std=c++11`

Building the testing program:

`g++ -o test.out braceExpand.t.cpp braceExpand.cpp -std=c++11`

## How to run the main program?
To run the main program, at the main directory:

Either, `make run` or, `./brace`

Then, pass in the input.

Another way:

`echo "{A,B,C}" | ./brace`

## How to run tests?
Make sure you first build the test executable by running:

`make test.out`

Then run,

`./test.out`

or,

`make runtest`
