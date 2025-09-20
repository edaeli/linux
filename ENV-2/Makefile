TARGET=complex_sort
CC=g++

all: $(TARGET)

main.o: main.cpp Complex.h Sort.h
	$(CC) $(CXXFLAGS) -c main.cpp -o main.o

Complex.o: Complex.cpp Complex.h
	$(CC) $(CXXFLAGS) -c Complex.cpp -o Complex.o

Sort.o: Sort.cpp Sort.h Complex.h
	$(CC) $(CXXFLAGS) -c Sort.cpp -o Sort.o

$(TARGET): main.o Complex.o Sort.o
	$(CC) main.o Complex.o Sort.o -o $(TARGET)

clean:
	rm -f *.o $(TARGET)

