#include <iostream>
#include <sstream>
#include "depgraph.hpp"

void bubblesort(int* A, int n) {
  for (int i=0; i<n; ++i) {
    for (int j=1; j<n; ++j) {

      {	std::stringstream ss; ss<<"("<<i<<","<<j<<")"; depgraph::newtask (ss.str()); }
      depgraph::hintlocation(i,j);

      //The accesses to A[j] and A[j-1] are declared out of the test
      //because it may or may not happen depending on the array.
      { std::stringstream ss; ss<<"A["<<j<<"]"; depgraph::readwrite (ss.str()); }
            
      { std::stringstream ss; ss<<"A["<<j-1<<"]"; depgraph::readwrite (ss.str()); }
      
      if (A[j] < A[j-1]) {
        int temp = A[j]; //There is no access to temp declared because
			 //the variable is inside the task
        A[j] = A[j-1];
        A[j-1] = temp;
      }
    }
  }
}



int main (int argc, char* argv[]) {
  int* arr;

  if (argc < 2) {
    std::cerr<<"Usage: "<<argv[0]<<" N [vizid1] [vizid2]";
  }
  
  int SIZE = atoi(argv[1]); //TODO: unsafe
  int completeviz = 1;
  int reducedviz = 2;
  if (argc > 2)
    completeviz = atoi(argv[2]); //TODO: unsafe
  if (argc > 3)
    reducedviz = atoi(argv[3]); //TODO: unsafe
  arr = new int[SIZE];
  
  for (int i=0; i<SIZE; ++i) {
    arr[i] = i*134+3542445%223;
  }

  bubblesort(arr, SIZE);

  depgraph::listall();

  depgraph::visualize(completeviz, true);
  depgraph::visualize(reducedviz, false);

  delete[] arr;
  
  return 0;
}
