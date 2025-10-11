CC = g++
TARGET = manual-append

all : $(TARGET)

manual-append.o : manual-append.cpp
	$(CC) -c manual-append.cpp -o manual-append.o

$(TARGET) : manual-append.o
	$(CC) manual-append.o -o $(TARGET)
	
clean:
	rm -f *.o $(TARGET)_
