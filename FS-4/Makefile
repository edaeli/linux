TARGET = redirect-cin
CC = g++


all: $(TARGET)

redirect-cin.o: redirect-cin.cpp
	$(CC)  -c redirect-cin.cpp -o redirect-cin.o

$(TARGET): redirect-cin.o
	$(CC) redirect-cin.o -o $(TARGET)

clean:
	rm -f *.o $(TARGET)

