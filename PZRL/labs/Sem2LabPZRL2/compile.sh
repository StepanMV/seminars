#!/bin/bash

g++ -c Vector.cpp
g++ -c LinkedList.cpp
g++ -c Stack.cpp

g++ Stack.o Vector.o LinkedList.o StackTest.o -o test -L./ -lCatch2Test

rm Stack.o
rm Vector.o
rm LinkedList.o
