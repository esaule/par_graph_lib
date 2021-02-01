CXXFLAGS=-std=c++14 -I ../bridges-cxx/src/ -I ../rapidjson/include/  -O3 -I ../includes
LDFLAGS=
LDLIBS=-l curl

LD=g++
CC=g++

BINS=bubble lcs matvec-1 matvec-2 weirdfibo weirdfibo-2 quicksort_original
OBJS=bubble.o lcs.o matvec-1.o matvec-2.o weirdfibo.o weirdfibo-2.o

all:$(BINS)

clean:
	-rm $(BINS)
	-rm $(OBJS)

depends:
	makedepend -I . -I ../includes -f Makefile *.cpp *.hpp

# DO NOT DELETE

bubble.o: ../includes/depgraph.hpp ../includes/depgraph_visualize.hpp
bubble.o: ../includes/depgraph_debug.hpp
weirdfibo.o: ../includes/depgraph.hpp ../includes/depgraph_visualize.hpp
weirdfibo.o: ../includes/depgraph_debug.hpp
