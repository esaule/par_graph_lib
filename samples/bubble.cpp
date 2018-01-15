#include <iostream>
#include <sstream>
#include "depgraph.hpp"

void bubblesort(int* A, int n) {
  for (int i=0; i<n; ++i) {
    for (int j=1; j<n; ++j) {

      {	std::stringstream ss; ss<<"("<<i<<","<<j<<")"; depgraph::newtask (ss.str()); }
            

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

#define SIZE 10
int arr[SIZE];

int main () {

  for (int i=0; i<SIZE; ++i) {
    arr[i] = i*134+3542445%223;
  }

  bubblesort(arr, SIZE);

  depgraph::listall();

  depgraph::visualize(1, true);
  depgraph::visualize(2, false);
  
  return 0;
}
