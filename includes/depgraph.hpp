#ifndef DEPGRAPH_HPP
#define DEPGRAPH_HPP

#include <queue>
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

  std::vector<int> processing_time;
  
  std::map<std::string, std::list<variableaccess> > accessmap;
  
  ///declares a new task with a given name
  ///@param name name of the task
  void newtask(const std::string& name) {
    tasklist.push_back(name);
    processing_time.push_back(1);
  }

  
  ///declares a new task. The name is the taskid 
  void newtask() {
    std::stringstream ss;
    ss<<tasklist.size()+1<<std::endl;
    newtask(ss.str());
  }

  void setprocessingtime(int pi) {
    processing_time[processing_time.size()-1] = pi;
  }

  ///declares that the current task reads the given variable
  ///@param name name of the variable read by the task
  void read(const std::string& name) {
    //assumes tasklist is not empty

    //TODO: should check for double insertion
    variableaccess va1 = {name, variableaccess::access::READ};
    accessmap[*(--(tasklist.end()))].push_back(va1);
  }

  ///declares that the current task writes the given variable
  ///@param name name of the variable writes by the task
  void write(const std::string& name) {
    //assumes tasklist is not empty

    //TODO: should check for double insertion
    variableaccess va2 = {name, variableaccess::access::WRITE}; 
    accessmap[*(--(tasklist.end()))].push_back(va2);
  }
  
  ///declares that the current task reads and writes the given variable
  ///@param name name of the variable reads and writes by the task
  void readwrite(const std::string& name) {
    read(name);
    write(name);
  }
  
}

#include "depgraph_visualize.hpp"

#include "depgraph_debug.hpp"


#endif
