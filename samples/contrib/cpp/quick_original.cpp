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
int partition(int array[], int low, int high){
  int pivot = array[high];
  int cLow = low-1;

  //Make a task for each partition using low and high and provide a hint location
  { std::stringstream ss; ss<<"("<<low<<","<<high<<")"; depgraph::newtask (ss.str()); }
  depgraph::hintlocation(low,high);

  for (int i = low; i <= high; i++){
    
    //Mark a swap
    { std::stringstream ss; ss<<"array["<<cLow<<"]"; depgraph::readwrite (ss.str()); }    
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
void quicksort(int array[], int low, int high){
  if (low < high){
    int partitionIndex = partition(array, low, high);

    quicksort(array, low, partitionIndex - 1);
    quicksort(array, partitionIndex + 1, high);
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
    arr[i] = i*134+3542445%223;
  }

  quicksort(arr, 0, SIZE - 1); //Call our quicksort

  depgraph::listall();

  depgraph::visualize(completeviz, true, true, "Quick Sort", "with transitive");
  depgraph::visualize(reducedviz, false, true, "Quick Sort", "without transitive");

  delete[] arr;
  
  return 0;
}
