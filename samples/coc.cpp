#include <iostream>
#include <sstream>
#include "depgraph.hpp"

//This is meant to be the chain on chain problem with dynamic programming. This is the right graph, thogh the code is clearly hacked up

void ChainOnChain(int N, int M) {

  for (int n=0; n<=N; ++n) {
    for (int m=1; m<=M; ++m) {

      {	std::stringstream ss; ss<<"("<<n<<","<<m<<")"; depgraph::newtask (ss.str()); }
      depgraph::hintlocation(n, m);

            
      { std::stringstream ss; ss<<"CC["<<n<<","<<m<<"]"; depgraph::readwrite (ss.str()); }

      for (int k=1; k<=n; ++k) {
	{ std::stringstream ss; ss<<"CC["<<k-1<<","<<m-1<<"]"; depgraph::read (ss.str()); }
      }
    }
  }
}



int main (int argc, char* argv[]) {
  int* arr;

  if (argc < 2) {
    std::cerr<<"Usage: "<<argv[0]<<" N [vizid1] [vizid2]"<<std::endl;
    return -1;
  }
  
  int SIZE = atoi(argv[1]); //TODO: unsafe
  int taskviz = 1;
  int accessviz = 2;
  int completeviz = 3;
  int reducedviz = 4;
  int cpviz = 5;
  if (argc > 2)
    taskviz = atoi(argv[2]); //TODO: unsafe
  if (argc > 3)
    accessviz = atoi(argv[3]); //TODO: unsafe
  if (argc > 4)
    completeviz = atoi(argv[4]); //TODO: unsafe
  if (argc > 5)
    reducedviz = atoi(argv[5]); //TODO: unsafe
  if (argc > 6)
    cpviz = atoi(argv[6]); //TODO: unsafe

  
  arr = new int[SIZE];

  ChainOnChain(6, 7);

  depgraph::listall();

  depgraph::visualize(taskviz, true, true, "Bubble Sort", "List all tasks", true, false);
  depgraph::visualize(accessviz, true, true, "Bubble Sort", "List tasks and access", true, true);
  depgraph::visualize(completeviz, true, false, "Bubble Sort", "Find dependencies", false, false);
  depgraph::visualize(reducedviz, false, false, "Bubble Sort", "Remove transitive dependencies", false, false);
  depgraph::visualize(cpviz, false, true, "Bubble Sort", "Identify critical path", false, false);

  
  delete[] arr;
  
  return 0;
}
