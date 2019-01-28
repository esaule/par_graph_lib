#include <iostream>
#include <sstream>
#include "depgraph.hpp"

int fibo (int p, std::string fibo_id) { //parameters 2 is only there to make the function show wel in par_graph_lib

  {std::stringstream ss; ss<<"fibo("<<p<<")-"<<fibo_id<<"-pre"; depgraph::newtask (ss.str()); }

  { std::stringstream ss; ss<<"p_"<<fibo_id; depgraph::read (ss.str()); }

  
  if (p < 2) {
    { std::stringstream ss; ss<<"r_"<<fibo_id; depgraph::write (ss.str()); }
    return 1;
  }
  std::string child1 = fibo_id+"1";
  std::string child2 = fibo_id+"2";

  { std::stringstream ss; ss<<"p_"<<child1; depgraph::write (ss.str()); }
  { std::stringstream ss; ss<<"p_"<<child2; depgraph::write (ss.str()); }

  
  int p1 = p-1;
  int p2 = p-2;

  int r1 = fibo(p1, child1);
  
  int r2 = fibo(p2, child2);

  {std::stringstream ss; ss<<"fibo("<<p<<")-"<<fibo_id<<"-post"; depgraph::newtask (ss.str()); }

  { std::stringstream ss; ss<<"r_"<<child1; depgraph::read (ss.str()); }
  { std::stringstream ss; ss<<"r_"<<child2; depgraph::read (ss.str()); }
  { std::stringstream ss; ss<<"r_"<<fibo_id; depgraph::write (ss.str()); }

  
  return r1 + r2;
}


int main (int argc, char* argv[]) {

  if (argc < 2) {
    std::cerr<<"Usage: "<<argv[0]<<" N [vizid1] [vizid2]"<<std::endl;
    return -1;
  }
  
  int SIZE = atoi(argv[1]); //TODO: unsafe
  int completeviz = 1;
  int reducedviz = 2;
  if (argc > 2)
    completeviz = atoi(argv[2]); //TODO: unsafe
  if (argc > 3)
    reducedviz = atoi(argv[3]); //TODO: unsafe
  
  fibo(SIZE, "");

  depgraph::listall();

  depgraph::visualize(completeviz, true, true, "Fibonacci", "with transitive");
  depgraph::visualize(reducedviz, false, true, "Fibonacci", "without transitive");

  return 0;
}
