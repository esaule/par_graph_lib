///This is a version of matvec where both loop level are used as task.
///Becasue sum is declared in the loop, the sum variable only causes a serialization of the j loop

#include <iostream>
#include <sstream>
#include "depgraph.hpp"

#define N 4

float A[N][N];
float x[N];
float y[N];


void matvec() {

  for (int i=0; i<N; ++i) {
    { std::stringstream ss; ss<<"matvec_"<<i<<"-pre"; depgraph::newtask (ss.str()); }
    { std::stringstream ss; ss<<"y["<<i<<"]"; depgraph::write (ss.str()); }


    y[i] = 0.;

    for (int j=0; j<N; ++j) {
      { std::stringstream ss; ss<<"matvec_"<<i<<"_"<<j; depgraph::newtask (ss.str()); }
      
      { std::stringstream ss; ss<<"A["<<i<<"]["<<j<<"]"; depgraph::read (ss.str()); }
      { std::stringstream ss; ss<<"x["<<j<<"]"; depgraph::read (ss.str()); }
      { std::stringstream ss; ss<<"y["<<i<<"]"; depgraph::readwrite (ss.str()); }
    
    
      y[i] += A[i][j] * x[j];
    }

    //note that there is not "-post" task really.

  }

}


int main () {


  for (int i=0; i<N; ++i) {
    x[i] = 0.;
    y[i] = 0.;
    
    for (int j=0; j<N; ++j) {
      A[i][j] = 0.;
    }
  }
  
  matvec();
  
  depgraph::listall();

  depgraph::visualize(1, true);
  depgraph::visualize(2, false);
  
  return 0;
}
