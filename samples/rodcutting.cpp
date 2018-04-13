#include <iostream>
#include <sstream>
#include "depgraph.hpp"

// A Dynamic Programming solution for Rod cutting problem
#include<stdio.h>
#include<limits.h>
 
// A utility function to get the maximum of two integers
int max(int a, int b) { return (a > b)? a : b;}
 
/* Returns the best obtainable price for a rod of length n and
   price[] as prices of different pieces */
int cutRod(int price[], int n)
{
   int val[n+1];
   val[0] = 0;
   int i, j;
 
   // Build the table val[] in bottom up manner and return the last entry
   // from the table
   for (i = 1; i<=n; i++)
   {
       val[i] = INT_MIN;
       //       for (j = 0; j < i; j++) {
       for (j = 0; j < i; j++) {
	 { std::stringstream ss; ss<<"("<<i<<","<<j<<")"; depgraph::newtask (ss.str()); }
	 { std::stringstream ss; ss<<"val["<<i<<"]"; depgraph::readwrite (ss.str()); }
	 { std::stringstream ss; ss<<"val["<<j<<"]"; depgraph::read (ss.str()); }
    	 
	 val[i] = max(val[i], price[i-j] + val[j]);
       }
   }
 
   return val[n];
}


/* Driver program to test above functions */
int main(int argc, char* argv[]) {

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
 
  int* arr = new int[SIZE];
  //making some boring test data
  for (int i=0; i<SIZE; ++i) {
    arr[i] = i;
  }
  
  printf("Maximum Obtainable Value is %dn", cutRod(arr, SIZE));
  
  depgraph::listall();
  
  depgraph::visualize(completeviz, true);
  depgraph::visualize(reducedviz, false);

  delete[] arr;
  
  return 0;
}

