//proposition by Datta Venkata S S S S Sabarish Bollapragada
//todo:
//-would be nicer with titles and parametric length, and assignment id
//-There is no array A in the code, so the variable dependencies are incorrect.

#include<iostream>
#include <sstream>
#include "depgraph.hpp"
 
using namespace std;
 
int main()
{
    int size, arr[50], i, j, temp;
    cout<<"Enter the array size : ";
    cin>>size;
    cout<<"Enter the array elements : ";
    for(i=0; i<size; i++)
    {
        cin>>arr[i];
    }
    cout<<"Now the Array before sorting is :\n";
    for(i=0; i<size; i++)
    {
        cout<<arr[i]<<" ";
    }
    for(i=0; i<size; i++)
    {
        for(j=i+1; j<size; j++)
        {
            { std::stringstream ss; ss<<"("<<i<<","<<j<<")"; depgraph::newtask (ss.str()); }
            depgraph::hintlocation(i, j);
            { std::stringstream ss; ss<<"arr["<<i<<"]"; depgraph::readwrite (ss.str()); }
            
            { std::stringstream ss; ss<<"A["<<j<<"]"; depgraph::readwrite (ss.str()); }
            if(arr[i]>arr[j])
            {
                temp=arr[i];
                arr[i]=arr[j];
                arr[j]=temp;
            }
        }
    }
    cout<<"Array after sorting is :\n";
    for(i=0; i<size; i++)
    {
        cout<<arr[i]<<" ";
    }
   depgraph::listall();

  depgraph::visualize(1, true);
  depgraph::visualize(2, false);
    return 0;
}
