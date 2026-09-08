CXX = g++
CXXFLAGS = -std=c++17 -O2 -Wall -Wextra

TARGET = matrix_multiplication
SRC = matrix_multiplication.cpp

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SRC)

clean:
	rm -f $(TARGET)