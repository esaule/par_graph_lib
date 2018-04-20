#include <iostream>
#include <sstream>
#include "depgraph.hpp"

int LCSLength(char* X, int m, char* Y, int n) {
  std::vector<std::vector<int>> C (m+1);
  for (int i=0; i <= m; ++i) {
    C[i].resize(n+1);
  }
  
  for (int i=0; i <= m; ++i) {
    { std::stringstream ss; ss<<"("<<i<<","<<0<<")"; depgraph::newtask (ss.str()); }
    depgraph::hintlocation(i, 0);
    { std::stringstream ss; ss<<"C["<<i<<"]["<<0<<"]"; depgraph::write (ss.str()); }
    
    C[i][0] = 0;
  }
  for (int j=0; j <= n; ++j) {
    { std::stringstream ss; ss<<"("<<0<<","<<j<<")"; depgraph::newtask (ss.str()); }
    depgraph::hintlocation(0, j);
    { std::stringstream ss; ss<<"C["<<0<<"]["<<j<<"]"; depgraph::write (ss.str()); }
    
    C[0][j] = 0;
  }
  for (int a=1; a <= m; ++a) {
    for (int b=1; b <= n; ++b){
      { std::stringstream ss; ss<<"("<<a<<","<<b<<")"; depgraph::newtask (ss.str()); }
    depgraph::hintlocation(a, b);
      { std::stringstream ss; ss<<"X["<<a-1<<"]"; depgraph::read (ss.str()); }
      { std::stringstream ss; ss<<"Y["<<b-1<<"]"; depgraph::read (ss.str()); }
      { std::stringstream ss; ss<<"C["<<a<<"]["<<b<<"]"; depgraph::write (ss.str()); }
      { std::stringstream ss; ss<<"C["<<a-1<<"]["<<b-1<<"]"; depgraph::read (ss.str()); }
      { std::stringstream ss; ss<<"C["<<a<<"]["<<b-1<<"]"; depgraph::read (ss.str()); }
      { std::stringstream ss; ss<<"C["<<a-1<<"]["<<b<<"]"; depgraph::read (ss.str()); }

      
      if (X[a-1] == Y[b-1]) {
        C[a][b] = C[a-1][b-1] + 1;
      } else {
        C[a][b] = max(C[a][b-1], C[a-1][b]);
      }
    }
  }
  return C[m][n];
}


int main (int argc, char* argv[]) {
  char* arr1;
  char* arr2;

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

  arr1 = new char[SIZE];
  arr2 = new char[SIZE];
  
  for (int i=0; i<SIZE; ++i) {
    arr1[i] = i*134+3542445%223;
    arr2[i] = i*134+3542445%223;
  }

  LCSLength(arr1, SIZE, arr2, SIZE);

  depgraph::listall();

  depgraph::visualize(completeviz, true, "Longest Common Subsequence", "with transitive");
  depgraph::visualize(reducedviz, false, "Longest Common Subsequence", "without transitive");

  delete[] arr1;
  delete[] arr2;
  
  return 0;
}
