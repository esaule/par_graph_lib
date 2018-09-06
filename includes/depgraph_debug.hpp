#ifndef DEPGRAPH_DEBUG_HPP
#define DEPGRAPH_DEBUG_HPP

#include <sstream>

namespace depgraph {

  std::string varAccessOfTask(const std::string& taskname) {
    std::stringstream ss;

    for (auto& p : accessmap[taskname]) {
      ss<<" "<<p.var<<" "<<(p.ac==variableaccess::access::READ?"R":"W")<<"\\n";
    }
      
    return ss.str();
  }
  
  void listall() {
    for (auto& ta : tasklist) {
      std::cout<<"task "<<ta<<std::endl;

      for (auto& p : accessmap[ta]) {
	std::cout<<"  use var "<<p.var<<" "<<(p.ac==variableaccess::access::READ?"R":"W")<<std::endl;
      }
    }
  }
}

#endif
