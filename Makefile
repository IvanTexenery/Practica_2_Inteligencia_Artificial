CXX = g++
CXXFLAGS = -Wall -g
BFS: InputOutput.o Grid.o BFS.o
	$(CXX) $(CXXFLAGS) -o  BFS  InputOutput.o BFS.o Grid.o
.PHONY: clean
clean:
	rm -rf *.o BFS