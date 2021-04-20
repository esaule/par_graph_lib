
#include <iostream>
#include <sstream>
#include "depgraph.hpp"

#define N 4
#define M 5

void indep() {
  for (int i=0; i<N; ++i) {
    for (int j=0; j<M; ++j) {
      { std::stringstream ss; ss<<i<<", "<<j; depgraph::newtask (ss.str()); }
      depgraph::hintlocation(i, j);
      
    }
 }
}

void indepparfori() {
  for (int i=0; i<N; ++i) {
    for (int j=0; j<M; ++j) {
      { std::stringstream ss; ss<<i<<", "<<j; depgraph::newtask (ss.str()); }
      depgraph::hintlocation(i, j);

      { std::stringstream ss; ss<<"A["<<i<<"]["<<j<<"]"; depgraph::read (ss.str()); }
      { std::stringstream ss; ss<<"A["<<i<<"]["<<j+1<<"]"; depgraph::readwrite (ss.str()); }

    }
 }
}

void indepparforj() {
  for (int i=0; i<N; ++i) {
    for (int j=0; j<M; ++j) {
      { std::stringstream ss; ss<<i<<", "<<j; depgraph::newtask (ss.str()); }
      depgraph::hintlocation(i, j);

      { std::stringstream ss; ss<<"A["<<i<<"]["<<j<<"]"; depgraph::write (ss.str()); }
      for (int fakej=0; fakej<M; ++fakej) {
	{ std::stringstream ss; ss<<"A["<<i+1<<"]["<<fakej<<"]"; depgraph::read (ss.str()); }
      }

    }
 }
}



int main () {
  //  indep();

  //indepparfori();
  indepparforj();
  
  depgraph::listall();

  depgraph::visualize(1, true);
  depgraph::visualize(2, false);
  
  return 0;
}
