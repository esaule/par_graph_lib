#include <iostream>
#include <sstream>
#include "depgraph.hpp"

int main (int argc, char* argv[]) {
  bridges::GraphAdjList<string, int> lemonpie;

  lemonpie.addVertex("1", 1);
  lemonpie.addVertex("2", 2);
  lemonpie.addVertex("3", 2);
  lemonpie.addVertex("4", 2);
  lemonpie.addVertex("5", 3);
  lemonpie.addVertex("6", 2);
  lemonpie.addVertex("7", 10);
  lemonpie.addVertex("8", 2);
  lemonpie.addVertex("9", 1);

  lemonpie.addVertex("10", 2);
  lemonpie.addVertex("11", 2);
  lemonpie.addVertex("12", 1);
  lemonpie.addVertex("13", 4);
  lemonpie.addVertex("14", 2);
  lemonpie.addVertex("15", 10);
  lemonpie.addVertex("16", 1);
  lemonpie.addVertex("17", 20);
  lemonpie.addVertex("18", 40);

  lemonpie.getVertex("1")->setLocation(20, 0);
  lemonpie.getVertex("2")->setLocation(130, 0);
  lemonpie.getVertex("3")->setLocation(20, -80);
  lemonpie.getVertex("4")->setLocation(130, -80);
  lemonpie.getVertex("5")->setLocation(75, -160);
  lemonpie.getVertex("6")->setLocation(120, -240);
  lemonpie.getVertex("7")->setLocation(220, -160);
  lemonpie.getVertex("8")->setLocation(220, -320);
  lemonpie.getVertex("17")->setLocation(300, -400);
  lemonpie.getVertex("16")->setLocation(350, -480);
  lemonpie.getVertex("18")->setLocation(350, -560);

  lemonpie.getVertex("9")->setLocation(350, 0);
  lemonpie.getVertex("10")->setLocation(300, -80);
  lemonpie.getVertex("11")->setLocation(420, -80);

  lemonpie.getVertex("12")->setLocation(350, -160);
  lemonpie.getVertex("14")->setLocation(470, -240);

  lemonpie.getVertex("13")->setLocation(350, -240);
  lemonpie.getVertex("15")->setLocation(420, -320);

  
  
  lemonpie.addEdge("1","3", 1);
  lemonpie.addEdge("2","4", 1);
  lemonpie.addEdge("3","5", 1);
  lemonpie.addEdge("4","5", 1);
  lemonpie.addEdge("5","6", 1);
  lemonpie.addEdge("6","8", 1);
  lemonpie.addEdge("7","8", 1);
  lemonpie.addEdge("8","17", 1);
  lemonpie.addEdge("17","16", 1);
  lemonpie.addEdge("16","18", 1);

  lemonpie.addEdge("9","10", 1);
  lemonpie.addEdge("9","11", 1);
  lemonpie.addEdge("10","12", 1);
  lemonpie.addEdge("11","12", 1);
  lemonpie.addEdge("12","13", 1);
  lemonpie.addEdge("13","15", 1);
  lemonpie.addEdge("14","15", 1);
  lemonpie.addEdge("15","16", 1);
    
  
  depgraph::animate_toplevel(lemonpie, 555);
  //depgraph::animate_listscheduling(lemonpie, 3, 777, 888);
  
  return 0;
}
