#!/bin/zsh

g++ -Wall -fexceptions -g -I . -c ./library.cpp -o library.o
g++ -Wall -fexceptions -g -I . -c ./main.cpp -o main.o

if [ $# -ne 1 ]
then
g++ -o test library.o main.o -lGL -lGLEW -lSDL2
else
g++ -o $1 library.o main.o -lGL -lGLEW -lSDL2
fi

