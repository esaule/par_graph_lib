//This is a contribution from Brandon Beckwith

#include <iostream>
#include <sstream>
#include "depgraph.hpp"

//Simple swap method
void swap(int* a, int* b){
  int t = *a;
  *a = *b;
  *b = t;
}

//quicksort partition
int partition(int array[], int low, int high, int depth){ //depth is just passed for layouting reason.
  int pivot = array[high];
  int cLow = low-1;

  //Make a task for each partition using low and high
  { std::stringstream ss; ss<<"partition("<<low<<","<<high<<")"; depgraph::newtask (ss.str()); } 
  //depgraph::hintlocation(low,high); // Probably should not provide a hint location like that Depth+low could be better?
  {depgraph::setprocessingtime(high-low+1);}
  depgraph::hintlocation(((high+low)/2)/3.,depth*.5); // this should give us a reasonnable layout
  
  for (int i = low; i <= high; i++){
    
    //Mark a swap
    { std::stringstream ss; ss<<"array["<<cLow+1<<"]"; depgraph::readwrite (ss.str()); } //there is a +1 here since cLow would be increased.
    { std::stringstream ss; ss<<"array["<<i<<"]"; depgraph::readwrite (ss.str()); }

    if (array[i] < pivot){
      cLow++;
      swap(&array[cLow], &array[i]);
    }
  }

  //Gotta account for the last swap
  { std::stringstream ss; ss<<"array["<<cLow + 1<<"]"; depgraph::readwrite (ss.str()); }       
  { std::stringstream ss; ss<<"array["<<high<<"]"; depgraph::readwrite (ss.str()); }

  swap(&array[cLow + 1], &array[high]);
  return cLow + 1;
}

//Simple recursive quicksort
void quicksort(int array[], int low, int high, int depth = 0){  //depth is just passed for layouting reason.
  if (low < high){
    int partitionIndex = partition(array, low, high, depth);

    quicksort(array, low, partitionIndex - 1, depth+1);
    quicksort(array, partitionIndex + 1, high, depth+1);
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

  quicksort(arr, 0, SIZE - 1); //Call our quicksort

  depgraph::listall();

  depgraph::visualize(completeviz, true, true, "Quick Sort", "with transitive");
  depgraph::visualize(reducedviz, false, true, "Quick Sort", "without transitive");

  auto a = depgraph::generate_bridges_graph(false, false, false, false, false);

  depgraph::animate_toplevel(a,555);
  
  delete[] arr;
  
  return 0;
}
