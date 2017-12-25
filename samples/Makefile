CXXFLAGS=-std=c++14 -I ../bridges/src/ -O3
LDFLAGS=-l curl

LD=g++
CC=g++

bubble: 


depends:
	makedepend -I . -f Makefile *.cpp *.hpp

# DO NOT DELETE

bubble.o: depgraph.hpp depgraph_visualize.hpp depgraph_debug.hpp
depgraph.o: depgraph_visualize.hpp depgraph_debug.hpp
