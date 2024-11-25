# Default target: clean and build main
all: main

# Rule to link the object files and create the executable
main: bin/main.o bin/Settlement.o src/Facility.cpp
	@echo 'Linking'
	g++ -o bin/main bin/main.o bin/Settlement.o src/Facility.cpp
	./bin/main

# Rule to compile the source files into object files
bin/main.o: src/main.cpp
	g++ -g -Wall -Weffc++ -std=c++11 -c -Iinclude -o bin/main.o src/main.cpp

# Rule to compile the source files into object files
bin/main.o: src/Facility.cpp
	g++ -g -Wall -Weffc++ -std=c++11 -c -Iinclude -o bin/Facility.o src/Facility.cpp

# Rule to compile the source files into object files
bin/Settlement.o: src/Settlement.cpp
	g++ -g -Wall -Weffc++ -std=c++11 -c -Iinclude -o bin/Settlement.o src/Settlement.cpp

# Clean the build directory
.PHONY: clean
clean:
	rm -f bin/*.o bin/main