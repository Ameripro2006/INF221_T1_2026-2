CXX = g++
CXXFLAGS = -std=c++17 -O2 -Wall -Wextra


SRCDIR = .
ALGODIR = algorithms
BINDIR = bin


MAIN_SRC = $(SRCDIR)/sorting.cpp


TARGETS = mergesort quicksort sort patiencesort
EXECUTABLES = $(patsubst %, $(BINDIR)/%, $(TARGETS))

.PHONY: all clean

all: $(BINDIR) $(EXECUTABLES)

$(BINDIR):
	mkdir -p $(BINDIR)

$(BINDIR)/%: $(MAIN_SRC) $(ALGODIR)/%.cpp
	$(CXX) $(CXXFLAGS) -o $@ $^

clean:
	rm -rf $(BINDIR)