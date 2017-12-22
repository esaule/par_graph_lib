#include <iostream>
#include <sstream>
#include <list>
#include <map>
#include <Bridges.h>
#include <GraphAdjList.h>
#include <vector>

namespace depgraph {

  struct variableaccess {
    std::string var;
    enum access{
      READ,
      WRITE
    } ac;
  };
  
  std::vector<std::string> tasklist;

  std::map<std::string, std::list<variableaccess> > accessmap;
  
  void newtask(const std::string& name) {
    tasklist.push_back(name);
  }
  
  void readwrite(const std::string& name) {
    //assume tasklist is not empty

    variableaccess va1 = {name, variableaccess::access::READ};
    accessmap[*(--(tasklist.end()))].push_back(va1);
    variableaccess va2 = {name, variableaccess::access::WRITE}; 
    accessmap[*(--(tasklist.end()))].push_back(va2);
  }

  void listall() {
    for (auto& ta : tasklist) {
      std::cout<<"task "<<ta<<std::endl;

      for (auto& p : accessmap[ta]) {
	std::cout<<"  use var "<<p.var<<" "<<(p.ac==variableaccess::access::READ?"R":"W")<<std::endl;
      }
    }
  }

  std::vector< std::list<int> > basic_graph;

  void build_graph() {

    basic_graph.resize(tasklist.size());
    
    for (int u=0; u<basic_graph.size(); ++u) {
      auto& s = tasklist[u];
      //"it" is before "s"
      for (int v = 0; v< u; ++v) {
	//all the variables access by it
	for (auto& va : accessmap[tasklist[v]]) {
	  auto varfind = std::find_if(accessmap[s].begin(), accessmap[s].end(), [&] (const variableaccess& v) { return v.var == va.var;});
	  if (varfind != accessmap[s].end() ) {
	    //NOT THE REAL CONDITION
	    if (va.ac !=variableaccess::access::READ ||
		varfind->ac !=variableaccess::access::READ) {
	      basic_graph[u].push_back(v);
	      //g.addEdge(*it, s, 1);
	    }
	  }
	}
      }
    }
    
  }
  
  void visualize(){
    build_graph();
    
    bridges::Bridges::initialize(1, "esaule", "182708497087");

    bridges::GraphAdjList<string,int> g;
    
    for (int u=0; u<basic_graph.size(); ++u) {
      g.addVertex(tasklist[u], 0);

      for (auto v : basic_graph[u]) {
	g.addEdge(tasklist[u], tasklist[v], 1);
      }
    }
    
    
    bridges::Bridges::setDataStructure(&g);
    bridges::Bridges::visualize();
  }
}

void bubblesort(int* A, int n) {
  for (int i=0; i<n; ++i) {
    for (int j=1; j<n; ++j) {

      {
	std::stringstream ss;
	ss<<"("<<i<<","<<j<<")";
	depgraph::newtask (ss.str());
      }
            
      
      {
	std::stringstream ss;
	ss<<"A["<<j<<"]";
	depgraph::readwrite (ss.str());
      }

            
      {
	std::stringstream ss;
	ss<<"A["<<j-1<<"]";
	depgraph::readwrite (ss.str());
      }
      if (A[j] < A[j-1]) {
        int temp = A[j];
        A[j] = A[j-1];
        A[j-1] = temp;
      }
    }
  }
}

#define SIZE 10
int arr[SIZE];

int main () {

  for (int i=0; i<SIZE; ++i) {
    arr[i] = i*134+3542445%223;
  }

  bubblesort(arr, SIZE);

  depgraph::listall();

  depgraph::visualize();

  
  return 0;
}
