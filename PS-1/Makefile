CC = g++
TARGET = do-command

all : $(TARGET)

do-command.o : do-command.cpp
	$(CC) -c do-command.cpp -o do-command.o

$(TARGET) :  do-command.o
	$(CC) do-command.o -o $(TARGET)

clean:
	rm -f *.o $(TARGET)
