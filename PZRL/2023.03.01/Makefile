.PHONY: dependencies clean

main.out: Vector2.o main.o
	g++-12 -std=c++20 -fmodules-ts Vector2.o main.o -o main.out
	make clean

main.o: main.cpp
	g++-12 -std=c++20 -fmodules-ts -c main.cpp

Vector2.o: Vector2.cpp
	g++-12 -std=c++20 -fmodules-ts -c Vector2.cpp

dependencies:
	g++-12 -std=c++20 -fmodules-ts -xc++-system-header iostream
	g++-12 -std=c++20 -fmodules-ts -xc++-system-header iomanip
	g++-12 -std=c++20 -fmodules-ts -xc++-system-header bitset
	g++-12 -std=c++20 -fmodules-ts -xc++-system-header cstdlib
	g++-12 -std=c++20 -fmodules-ts -xc++-system-header ctime
	g++-12 -std=c++20 -fmodules-ts -xc++-system-header vector

clean:
	rm *.o
