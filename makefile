# Default target: clean and build main
all: compile main 

# Rule to link the object files and create the executable
main: 
	g++ bin/main bin/*.o
	./bin/main

# Rule to compile the source files into object files
compile:
	g++ -g -Wall -Weffc++ -std=c++11 -c -Iinclude -o bin/main.o src/main.cpp
	g++ -g -Wall -Weffc++ -std=c++11 -c -Iinclude bin/*.o src/*.cpp

# Clean the build directory
.PHONY: clean
clean:
	rm -f bin/*.o bin/main