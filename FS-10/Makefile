CC = g++
TARGET = copy

all : $(TARGET)

copy.o : copy.cpp
	$(CC) -c copy.cpp -o copy.o

$(TARGET) :  copy.o
	$(CC) copy.o -o $(TARGET)

clean:
	rm -f *.o $(TARGET)
