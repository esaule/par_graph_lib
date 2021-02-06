#include <iostream>
#include <sstream>
#include "depgraph.hpp"

int main (int argc, char* argv[]) {
  bridges::GraphAdjList<string, int> indep;


  for (int i=0; i< 20; ++i) {
    std::string task = std::to_string(i);
    
    indep.addVertex(task, rand() % 10);
    
    indep.getVertex(task)->setLocation(i*80, 0);
  }
    
  
  //depgraph::animate_toplevel(lemonpie, 555);
  try {
    depgraph::animate_listscheduling(indep, 4, 777, 888);
  } catch (const char* c){
    std::cerr<<"exception: "<<c<<"\n";
  }
  
  return 0;
}
