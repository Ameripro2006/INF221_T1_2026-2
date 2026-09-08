CXX = g++
CXXFLAGS = -std=c++17 -O3 -Wall -Wextra

# Directorios
SRCDIR = .
ALGODIR = algorithms
BINDIR = bin

# Archivo principal de medición
MAIN_SRC = $(SRCDIR)/sorting.cpp

# Algoritmos a compilar
TARGETS = mergesort quicksort sort patiencesort
EXECUTABLES = $(patsubst %, $(BINDIR)/%, $(TARGETS))

.PHONY: all clean

all: $(BINDIR) $(EXECUTABLES)

# Crear directorio bin si no existe
$(BINDIR):
	mkdir -p $(BINDIR)

# Regla para compilar cada algoritmo vinculándolo con sorting.cpp
$(BINDIR)/%: $(MAIN_SRC) $(ALGODIR)/%.cpp
	$(CXX) $(CXXFLAGS) -o $@ $^

clean:
	rm -rf $(BINDIR)