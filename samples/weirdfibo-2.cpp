///This is a version of weirdfibo where many tasks are created for
///each iteration of the inner loop of the calculation.

#include <iostream>
#include <sstream>
#include "depgraph.hpp"

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
    { std::stringstream ss; ss<<"fibo_"<<i<<"-pre"; depgraph::newtask (ss.str()); }

    { std::stringstream ss; ss<<"fibo_v["<<i<<"]"; depgraph::write (ss.str()); }
    fibo_v[i] = 0;
    for (int j=0; j<DISTANCE; ++j) {
      { std::stringstream ss; ss<<"fibo_"<<i<<"_"<<j; depgraph::newtask (ss.str()); }


      { std::stringstream ss; ss<<"fibo_v["<<i-j-DISTANCE<<"]"; depgraph::read (ss.str()); }
      { std::stringstream ss; ss<<"fibo_v["<<i<<"]"; depgraph::readwrite (ss.str()); }
      
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
