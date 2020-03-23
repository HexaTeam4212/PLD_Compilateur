# C compiler with antlr4/c++

[![Build Status](https://travis-ci.com/HexaTeam4212/PLD_Compilateur.svg?branch=master)](https://travis-ci.com/HexaTeam4212/PLD_Compilateur)

## Instructions

This minimal example shows how to build a basic C compiler using Antlr4 for C++. The only file the compiler can deal with is:

```
int main() {
   return n;
}
```
where `n` is a positive integer. 

## Source Files
- `ifcc.g4` contains the grammar in antlr4 format
- `main.cpp` contains the C++ code to call the antlr4-generated parser on the  file name provided in the command line.
- `visitor.h` is a visitor of the parse tree that produces an assembly-language output

## Compilation scripts
- `Makefile` can be used to compile the parser. Libraries and include directories default to the values that work in the IF machines of rooms 208 and 219.
- `compile_ubuntu.sh` is a script that compiles the project in a different environment (a ubuntu where the antlr runtime had to be compiled manually).
- `compile_docker.sh` is a script to use if you are desperate. It compiles the project in a docker environment where antlr4 and its dependencies are properly installed. 

## Instructions for docker run

The two scripts `run.sh` and `stop.sh` can be used to automaticaly run and stop a container for the project.  

The run script will create a container with everything you need to make the project compile. Once running, you can modify your source files and they will directly be available inside the container, no need to rerun the container.  
If you close the console which was inside the container, the run script will give access again to the shell witout restarting the container.  

The stop script simply stop and delete the container.