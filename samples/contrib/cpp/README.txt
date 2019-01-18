Brandon Beckwith

I looked over the algorithm again, but I couldn't really find any issues with it. I went ahead and looked up and double checked the algorithm and it seems fine. I'm using the Lomuto partition scheme. I also added a debug printout showing the initial and final array and everything sorts correctly.

So my next step was to run the algorithm using a series of different arrays. I have included them as separate files.

There are 4 .cpp files that each have an image in the image folder.

The original file (quick_original.cpp) was the original submission and used an initial array that is already sorted.

quick_increasing.cpp is essentially the same as the original and features an already sorted array, but includes the modifications I made to the program.

quick_decreasing.cpp features an array in decreasing order and produces a graph similar to the increasing, but isn't as spread out.

quick_rand.cpp produces the most sporadic graphs since the ordering of the array is random. The graphs come out looking deformed and disconnected.

Finally I included one more graph screenshot that I found interesting. It was a copy of decreasing that had an extra hint location thrown in the partition for loop for cLow and i. It has a nice spiral shape to it, but is essentially the same as the decreasing one.

I don't think there is anything wrong with the algorithm and I'm not really sure where to go from here.

The last one I ran was for quick_increasing so the graph on the site is the increasing one.

//Original
A simple implementation of quicksort. A screen shot of the graph is included.

In order to make the algorithm more parallel the partition method would need to be parallelized.
Which I'm not doing at this time :/

If you like this and would like me to submit a pull request, please just let me know.

Build info:

time to build viz: 0.000916s
Success: Assignment posted to the server. 
Check out your visualization at:

http://bridges-cs.herokuapp.com/assignments/1/bbeckwi2

time to build viz: 0.000308s
Success: Assignment posted to the server. 
Check out your visualization at:

http://bridges-cs.herokuapp.com/assignments/2/bbeckwi2
