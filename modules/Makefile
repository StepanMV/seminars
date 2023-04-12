.PHONY: dependencies clean

main.out: ArraysMisc.o ArraySorts.o Timer.o CppMisc.o main.o
	g++-12 -std=c++20 -fmodules-ts main.o CppMisc.o ArraysMisc.o ArraySorts.o Timer.o -o main.out
	make clean

main.o: main.cpp
	g++-12 -std=c++20 -fmodules-ts -c main.cpp

CppMisc.o: CppMisc.cpp
	g++-12 -std=c++20 -fmodules-ts -c CppMisc.cpp

ArraysMisc.o: ArraysMisc.cpp
	g++-12 -std=c++20 -fmodules-ts -c ArraysMisc.cpp

ArraySorts.o: ArraySorts.cpp
	g++-12 -std=c++20 -fmodules-ts -c ArraySorts.cpp

Timer.o: Timer.cpp
	g++-12 -std=c++20 -fmodules-ts -c Timer.cpp

dependencies:
	g++-12 -std=c++20 -fmodules-ts -xc++-system-header iostream
	g++-12 -std=c++20 -fmodules-ts -xc++-system-header bitset
	g++-12 -std=c++20 -fmodules-ts -xc++-system-header array
	g++-12 -std=c++20 -fmodules-ts -xc++-system-header chrono
	g++-12 -std=c++20 -fmodules-ts -xc++-system-header cstddef
	g++-12 -std=c++20 -fmodules-ts -xc++-system-header cstdlib
	g++-12 -std=c++20 -fmodules-ts -xc++-system-header ctime
	g++-12 -std=c++20 -fmodules-ts -xc++-system-header sstream
	g++-12 -std=c++20 -fmodules-ts -xc++-system-header string
	g++-12 -std=c++20 -fmodules-ts -xc++-system-header vector

clean:
	rm *.o
