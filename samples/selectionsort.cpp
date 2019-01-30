//sample proposed by Datta Venkata S S S S Sabarish Bollapragada
#include <iostream>
#include <sstream>
#include "depgraph.hpp"

void selectionsort(int* arr, int n) {

    for(int i=0; i<n; i++)
    {
        for(int j=i+1; j<n; j++)
        {
            { std::stringstream ss; ss<<"("<<i<<","<<j<<")"; depgraph::newtask (ss.str()); }
            depgraph::hintlocation(i, j);
            { std::stringstream ss; ss<<"arr["<<i<<"]"; depgraph::readwrite (ss.str()); }
            
            { std::stringstream ss; ss<<"arr["<<j<<"]"; depgraph::readwrite (ss.str()); }
            if(arr[i]>arr[j])
            {
	      int temp=arr[i];
	      arr[i]=arr[j];
	      arr[j]=temp;
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
  int completeviz = 1;
  int reducedviz = 2;
  if (argc > 2)
    completeviz = atoi(argv[2]); //TODO: unsafe
  if (argc > 3)
    reducedviz = atoi(argv[3]); //TODO: unsafe
  arr = new int[SIZE];
  
  for (int i=0; i<SIZE; ++i) {
    arr[i] = (i*134+3542445)%223;
  }

  selectionsort(arr, SIZE);

  for (int i=0; i<SIZE; ++i) {
    std::cout<<arr[i]<<" ";
  }
  std::cout<<std::endl;
  
  
  depgraph::listall();

  depgraph::visualize(completeviz, true, true, "Selection Sort", "with transitive");
  depgraph::visualize(reducedviz, false, true, "Selection Sort", "without transitive");

  delete[] arr;
  
  return 0;
}
