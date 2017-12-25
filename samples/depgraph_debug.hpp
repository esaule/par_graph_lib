#ifndef DEPGRAPH_DEBUG_HPP
#define DEPGRAPH_DEBUG_HPP

namespace depgraph {
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
