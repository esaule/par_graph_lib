# par_graph_lib

## Getting Started

This is the repository for par_graph_lib, a tool used at UNC Charlotte
to teach Parallel Computing.

To install it, I assume you have a linux distribution or that you will
know how to adapt this for your use case.

First clone the project from github while gettign the submodules with :

```$ git clone --recurse-submodules https://github.com/esaule/par_graph_lib.git```

Go into that directory:

```$ cd par_graph_lib/```

There are four directories in there. `bridges-cxx/` and `rapidjson/`
are external dependencies. `includes/` is the library itself. If you
just want to use the library to see the dependency graph of some
algorithms `samples/` is the only directory you need to worry
about. So go in there

```$ cd samples/```

There are a bunch of sample codes in there using the library. You can
compile bubble sort with

```$ make bubble```

you can run it on an array of size 6 with :

```$ ./bubble 6```

This should tell you that you do not have the permission neccesarry to
upload visualization. You will need to make an account on
http://bridges-cs.herokuapp.com/ and go to the profile page once the
account is created, not the username and API key.

Create a file in your home directory called `.pargraphrc`. This file
should contain two lines, the first one is the username and the second
one is the apikey. For me, the file contains:

```
esaule
0123456789
```

Now running the bubble sort code should give you a visualization

```$ ./bubble 6```

This returns this URL for me:
http://bridges-cs.herokuapp.com/assignments/2/esaule (assuming I
haven't run something else since you should see the bubble sort
visualization at that address). You can see additional information by
activating the node and link labels.

## Extracting dependencies of your own code

TO COME