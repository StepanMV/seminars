.PHONY: dependencies clean

main.out: RGBA.o main.o
	g++-12 -std=c++20 -fmodules-ts main.o RGBA.o -o main.out
	make clean

main.o: main.cpp
	g++-12 -std=c++20 -fmodules-ts -c main.cpp

RGBA.o: RGBA.cpp
	g++-12 -std=c++20 -fmodules-ts -c RGBA.cpp

dependencies:
	g++-12 -std=c++20 -fmodules-ts -xc++-system-header iostream
	g++-12 -std=c++20 -fmodules-ts -xc++-system-header iomanip
	g++-12 -std=c++20 -fmodules-ts -xc++-system-header bitset
	g++-12 -std=c++20 -fmodules-ts -xc++-system-header cstdlib
	g++-12 -std=c++20 -fmodules-ts -xc++-system-header ctime
	g++-12 -std=c++20 -fmodules-ts -xc++-system-header vector

clean:
	rm *.o
