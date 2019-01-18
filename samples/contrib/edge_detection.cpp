/*
Rishiraj Manwatkar
801021027
Parallel Computing
Assignment: Extra Credit Question : New samples in par_graph_lib

Implemented 2-D image convolution to find out image's x-gradient (x-edge)

In this code, I have taken random image of NxM Bytes size.
The Kernel is Sobel operator which is 3x3

I have embedded par_graph_lib into this code to analyse the dependencies.

To build this code just use:~ make edge

//access to Kernel and src are ignored.

*/

#include <iostream>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include "depgraph.hpp"

using namespace std;

#define N (4)
#define M (4)
#define K (3)

//Input Image
int ipImage[N][M];

//Output Image
float opImage[N][M];


//Sobel operator to find out x-gradients (x-edge)
float kernel[K][K] = {
					{1, 0, -1},
					{2, 0, -2},
					{1, 0, -1} };

//Helper function
int helper(int m, int x)
{

    if(x >= m)
        return 2*m - x - 1;

    if(x < 0)
        return -x - 1;

   return x;
}


/*Mirroring mechanism to accommodate the convolution
operation along the input image's 4 borders*/
void mirroring(int src[N][M], float dst[N][M], float Kernel[K][K])
{
    int x1, y1;
    float sum;
    for(int y = 0; y < N; y++)
    {
        for(int x = 0; x < M; x++)
        {
        	{ std::stringstream ss; ss<<"ipIm_"<<x<<"_"<<y; depgraph::newtask (ss.str()); }
    		depgraph::hintlocation(x, y);

    		{ std::stringstream ss; ss<<"sum"; depgraph::write (ss.str()); }
            sum = 0.0;

            for(int k = -1;k <= 1; k++)
            {
                for(int j = -1;j <= 1; j++ )
                {
                    x1 = helper(M, x - j);
                    y1 = helper(N, y - k);
				    { std::stringstream ss; ss<<"sum"; depgraph::readwrite (ss.str()); }
                    sum = sum + Kernel[j+1][k+1] * src[y1][x1];
                }
  	       	}

  	       	{ std::stringstream ss; ss<<"dest["<<y<<x<<"]"; depgraph::write (ss.str()); }
		    { std::stringstream ss; ss<<"sum"; depgraph::read (ss.str()); }
            dst[y][x] = sum;
        }
    }
}

int main(int argc, char *argv[])
{

	srand(time(0));


	//Create input image of size NxM
	for(int i=0; i<N; i++)
	{
		for(int j=0; j<N; j++)
		{
			ipImage[i][j] = rand()%10;
		}
	}

	//Display it
	cout << "Input Image of size: ["<<N<<" X "<<M<<"]"<< endl;
	for(int i=0; i<N; i++)
	{
		for(int j=0; j<N; j++)
		{
			cout << ipImage[i][j] << "\t";
		}
		cout << endl;
	}
	cout << endl;


	//Do the convolution to find out x-gradients in the input image
	mirroring(ipImage, opImage, kernel);
	depgraph::listall();

	depgraph::visualize(1, false);
	depgraph::visualize(2, true);

	//Display output image which contains x-gradient information of the input image
	cout << "Output Image of size: ["<<N<<" X "<<M<<"]"<< endl;
	for(int i=0; i<N; i++)
	{
		for(int j=0; j<N; j++)
		{
			cout << opImage[i][j] << "\t";
		}
		cout << endl;
	}
	cout << endl;

	return 0;
}
