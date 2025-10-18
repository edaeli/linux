CXX = g++
CXXFLAGS = -Wall -std=c++17
TARGET = shell

all: $(TARGET)

$(TARGET): shell.cpp
	$(CXX) $(CXXFLAGS) -o $(TARGET) shell.cpp

clean:
	rm -f $(TARGET) *.log

