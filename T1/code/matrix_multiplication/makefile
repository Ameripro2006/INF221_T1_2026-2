CXX = g++
CXXFLAGS = -O2 -std=c++17 -Wall

TARGET = matrix_multiplication
SRC = matrix_multiplication.cpp

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC)

clean:
	rm -f $(TARGET)