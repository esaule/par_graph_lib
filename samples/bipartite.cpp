#include <iostream>
#include <sstream>
#include "depgraph.hpp"

int main (int argc, char* argv[]) {
  bridges::GraphAdjList<string, int> bipartite;

  int nbtaskl = 5;
  int nbtaskr = 6;

  for (int i=0; i<nbtaskl; ++i) {
    std::string l = "l" + std::to_string(i);
    bipartite.addVertex(l, 1);    
    bipartite.getVertex(l)->setLocation(0, i*50);
  }

  for (int j=0; j<nbtaskr; ++j) {
    std::string r = "r" + std::to_string(j);
    bipartite.addVertex(r, 1);    
    bipartite.getVertex(r)->setLocation(70, j*50);
  }

  for (int i=0; i< nbtaskl; ++i) {
    std::string l = "l" + std::to_string(i);
    for (int j=0; j< nbtaskr; ++j) {
      std::string r = "r" + std::to_string(j);

      if (rand()%100 > 65)
	bipartite.addEdge(l, r, 1);
      
    }

  }
  
  //depgraph::animate_toplevel(bipartite, 555);
  depgraph::animate_listscheduling(bipartite, 3, 777, 888, false);
  
  return 0;
}
