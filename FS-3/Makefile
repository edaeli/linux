CC = g++
TARGET = hacker

all : $(TARGET)

hacker.o : hacker.cpp
	$(CC) -c hacker.cpp -o hacker.o

$(TARGET) : hacker.o
	$(CC) hacker.o -o $(TARGET)

clean:
	rm -f *.o $(TARGET)
	


