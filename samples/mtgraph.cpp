#include <iostream>
#include <sstream>
#include "depgraph.hpp"

int main (int argc, char* argv[]) {
  bridges::GraphAdjList<string, int> lemonpie;

  lemonpie.addVertex("A", 3);
  lemonpie.addVertex("B", 4);
  lemonpie.addVertex("C", 7);
  lemonpie.addVertex("D", 4);
  lemonpie.addVertex("E", 2);
  lemonpie.addVertex("F", 1);
  lemonpie.addVertex("G", 5);
  lemonpie.addVertex("H", 3);
  lemonpie.addVertex("I", 2);
  lemonpie.addVertex("J", 1);
  lemonpie.addVertex("K", 6);
  lemonpie.addVertex("L", 3);


  int levelsp = 50;
  
  lemonpie.getVertex("A")->setLocation(0*levelsp, 0);
  lemonpie.getVertex("B")->setLocation(0*levelsp, 50);

  lemonpie.getVertex("C")->setLocation(1*levelsp, 0);
  lemonpie.getVertex("D")->setLocation(1*levelsp, 50);
  lemonpie.getVertex("E")->setLocation(1*levelsp, 100);

  lemonpie.getVertex("G")->setLocation(2*levelsp, 0);
  lemonpie.getVertex("H")->setLocation(2*levelsp, 50);
  lemonpie.getVertex("I")->setLocation(2*levelsp, 100);

  lemonpie.getVertex("F")->setLocation(3*levelsp, 20);
  
  lemonpie.getVertex("J")->setLocation(4*levelsp, 0);
  lemonpie.getVertex("K")->setLocation(4*levelsp, 50);

  lemonpie.getVertex("L")->setLocation(5*levelsp, 50);
  

  
  lemonpie.addEdge("A","C", 1);
  lemonpie.addEdge("A","D", 1);

  lemonpie.addEdge("B","D", 1);
  lemonpie.addEdge("B","E", 1);
  
  lemonpie.addEdge("C","G", 1);

  lemonpie.addEdge("D","G", 1);
  
  lemonpie.addEdge("E","G", 1);
  lemonpie.addEdge("E","H", 1);
  lemonpie.addEdge("E","I", 1);

  lemonpie.addEdge("G","F", 1);

  lemonpie.addEdge("H","J", 1);

  lemonpie.addEdge("I","J", 1);
  lemonpie.addEdge("I","K", 1);

  lemonpie.addEdge("F","J", 1);

  lemonpie.addEdge("J","L", 1);
  
  lemonpie.addEdge("K","L", 1);
	  
  
  //depgraph::animate_toplevel(lemonpie, 555);
  depgraph::animate_listscheduling(lemonpie, 3, 777, 888, false);
  
  return 0;
}
