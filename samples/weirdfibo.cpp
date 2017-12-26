#include <iostream>
#include <sstream>
#include "depgraph.hpp"

void bubblesort(int* A, int n) {
  for (int i=0; i<n; ++i) {
    for (int j=1; j<n; ++j) {

            
            
      { std::stringstream ss; ss<<"A["<<j-1<<"]"; depgraph::readwrite (ss.str()); }
      

    }
  }
}

#define N 50
#define DISTANCE 3

int fibo_v[N];


void fibo() {
  for (int i=0; i<2*DISTANCE; ++i) {
    { std::stringstream ss; ss<<"fibo_"<<i; depgraph::newtask (ss.str()); }
    { std::stringstream ss; ss<<"fibo_v["<<i<<"]"; depgraph::write (ss.str()); }
      
    fibo_v[i] = 1;
  }
  for(int i=2*DISTANCE; i<N; ++i) {
    { std::stringstream ss; ss<<"fibo_"<<i; depgraph::newtask (ss.str()); }
    { std::stringstream ss; ss<<"fibo_v["<<i<<"]"; depgraph::write (ss.str()); }
    fibo_v[i] = 0;
    for (int j=0; j<DISTANCE; ++j) {
      { std::stringstream ss; ss<<"fibo_v["<<i-j-DISTANCE<<"]"; depgraph::read (ss.str()); }
      
      fibo_v[i] += fibo_v[i-j-DISTANCE];
    }
  }
}


int main () {

  fibo();

  depgraph::listall();

  depgraph::visualize(1, true);
  depgraph::visualize(2, false);
  
  return 0;
}
