CXX ?= g++
CXXFLAGS = -std=c++11 -Wall

gronsfeld: main.cpp modAlphaCipher.cpp modAlphaCipher.h
	$(CXX) $(CXXFLAGS) main.cpp modAlphaCipher.cpp -o gronsfeld

clean:
	rm -f gronsfeld
