CXX ?= g++
CXXFLAGS = -std=c++11 -Wall

transposition: main.cpp modTableCipher.cpp modTableCipher.h
	$(CXX) $(CXXFLAGS) main.cpp modTableCipher.cpp -o transposition

clean:
	rm -f transposition
