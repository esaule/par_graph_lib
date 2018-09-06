#ifndef DEPGRAPH_VIZ_HPP
#define DEPGRAPH_VIZ_HPP

#include <chrono>
#include <iostream>
#include <fstream>

#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>

namespace depgraph {

  //s is the graphs to remove transitive edges from
  //u is the vertex to remove outgoing edges from
  void remove_transitive_node(std::vector< std::list<int> >& s,
			      int u) {
    std::vector<bool> reachable(s.size(), false);
    std::deque<int> q;

    for (auto v : s[u]) {
      q.push_back(v);
    }

    while (!(q.empty())) {
      auto x = q.front();
      q.pop_front();

      //reachability of neighboors of x
      for (auto y : s[x]) {
	if (!reachable[y]) {
	  reachable[y] = true;
	  q.push_back(y);
	}
      }
    }

    s[u].remove_if([&](const int & a){ return reachable[a];}  );
  }
  
  void remove_transitive(const std::vector< std::list<int> >& bg,
			 std::vector< std::list<int> >& s) {
    s.clear();
    s = bg;

    for (int x=0; x<bg.size(); ++x)
      remove_transitive_node(s, x);    
  }

  std::vector< std::list<int> > basic_graph;

  std::vector< std::list<int> > simplified_graph;

  ///@param u task id
  ///@param v task id
  ///assumes u < v
  ///@returns true if u an v have a RAW, WAW, WAR dependency
  bool depends_on (int u, int v) {
    auto& s = tasklist[u];
    //all the variables access by it
    for (auto& va : accessmap[tasklist[v]]) {
      auto varfind = std::find_if(accessmap[s].begin(), accessmap[s].end(), [&] (const variableaccess& v) { return v.var == va.var;});
      if (varfind != accessmap[s].end() ) {
	//NOT THE REAL CONDITION
	if (va.ac !=variableaccess::access::READ ||
	    varfind->ac !=variableaccess::access::READ) {
	  return true;
	  //g.addEdge(*it, s, 1);
	}
      }
    }

    return false;
  }

  ///@param u task id
  ///@param v task id
  ///assumes u < v
  ///@return string of all variable that cause a dependency from u to v
  std::string why_depends_on(int u, int v) {
    std::stringstream ss;
    
    auto& s = tasklist[u];
    //all the variables access by it
    for (auto& va : accessmap[tasklist[v]]) {
      auto varfind = std::find_if(accessmap[s].begin(), accessmap[s].end(), [&] (const variableaccess& v) { return v.var == va.var;});
      if (varfind != accessmap[s].end() ) {
	//NOT THE REAL CONDITION
	if (va.ac !=variableaccess::access::READ ||
	    varfind->ac !=variableaccess::access::READ) {
	  ss<<va.var<<" ";
	  //g.addEdge(*it, s, 1);
	}
      }
    }

    return ss.str();
  }
  
  void build_graph() {
    basic_graph.resize(tasklist.size());
    
    for (int u=0; u<basic_graph.size(); ++u) {
    
      //"it" is before "s"
      for (int v = 0; v< u; ++v) {

	if (depends_on (u,v))
	  basic_graph[v].push_back(u);
      }
    }
  }

  bridges::GraphAdjList<string,int> g;


  std::vector<int> toplevel;
  std::vector<int> predecessor;
  int sinkvertex;
  
  //this algorithm works because the vertices are topo sorted
  void highlight_criticalpath() {
    

    if (toplevel.size() == 0) {

      if (simplified_graph.size() == 0) //not built
	remove_transitive(basic_graph, simplified_graph);

      
      toplevel = std::vector<int> (simplified_graph.size(), 0);
      predecessor = std::vector<int> (simplified_graph.size(), -1);
      
      int maxlevel = 0;
      sinkvertex = -1;
      
      //compute top level, predecessor, and maxlevel
      for (int u=0; u<simplified_graph.size(); ++u) {
	toplevel[u] += processing_time[u];
	
	for (auto v : simplified_graph[u]) {
	  if (toplevel[u] > toplevel[v]) {
	    toplevel[v] = toplevel[u];
	    predecessor[v] = u;
	  }
	}
	
	if (toplevel[u] > maxlevel) {
	  maxlevel = toplevel[u];
	  sinkvertex = u;
	}
      }
    }

    int x = sinkvertex;
    int prev = sinkvertex; //previous vertex in the reconstructed path (so the next according to the topological order
    while (x >= 0) {
      //x is on the critical path      

      //color x in red
      auto vert_x_p = g.getVertices()->find(tasklist[x])->second;
      auto vert_viz_p = vert_x_p->getVisualizer();
      vert_viz_p->setColor(bridges::Color(255,0,0));
      
      //color the edge
      if (x != prev) {
	auto vert_prev_p = g.getVertices()->find(tasklist[prev])->second;
	auto link_viz_p = vert_x_p->getLinkVisualizer(vert_prev_p);
	link_viz_p->setThickness(bridges::LinkVisualizer::DEFAULT_THICKNESS * 10.);
	link_viz_p->setColor(bridges::Color(255,0,0));
      }

      prev = x;
      x = predecessor[x];
    }
    
  }

  void get_bridges_account (std::string& username,
			    std::string& apikey) {

    std::string configdir_name;

    const char *homedir;

    if ((homedir = getenv("HOME")) == NULL) {
      homedir = getpwuid(getuid())->pw_dir;
    }
    
    std::string filename;
    {
      std::stringstream ss;
      ss<<homedir<<"/.pargraphrc";
      filename = ss.str();
    }

    std::ifstream in (filename.c_str());
    if (!in) {
      std::cerr<<"can't read "<<filename<<std::endl;
      std::cerr<<"should contain bridges username on the first line and bridges apikey on the second line. Create an account on http://bridges-cs.herokuapp.com/"<<std::endl;
      return;
    }
    in >> username;
    in >> apikey;
    if (!in) {
      std::cerr<<"can't read "<<filename<<std::endl;
      std::cerr<<"should contain bridges username on the first line and bridges apikey on the second line. Create an account on http://bridges-cs.herokuapp.com/"<<std::endl;
      return;
    }
  }
  

  void visualize(int channel,
		 bool use_simple = false,
		 bool highlightCP = true,
		 std::string title = "",
		 std::string description = ""
		 ) {

    auto start = std::chrono::system_clock::now();

    std::string bridges_user;
    std::string bridges_apikey;

    get_bridges_account(bridges_user, bridges_apikey);
    
    bridges::Bridges::initialize(channel, bridges_user, bridges_apikey);

    bridges::Bridges::setTitle(title);
    bridges::Bridges::setDescription(description);

    if (basic_graph.size() == 0) //if not built
      build_graph();

    if ((!use_simple) 
	&& simplified_graph.size() == 0) //not built
      remove_transitive(basic_graph, simplified_graph);

    g = bridges::GraphAdjList<string,int>();

    for (int u=0; u<tasklist.size(); ++u) {
      g.addVertex(tasklist[u], 0);

      auto lh = hints.find(tasklist[u]);
      if (lh != hints.end()) {
	auto elem_viz_p = g.getVertex(tasklist[u])->getVisualizer();
	elem_viz_p -> setLocation(lh->second.i*100., lh->second.j*100.);
      }
    }
    
    for (int u=0; u<tasklist.size(); ++u) {
      for (auto v : (use_simple?basic_graph:simplified_graph)[u]) {
	g.addEdge(tasklist[u], tasklist[v], 1);
	auto link_viz_p = g.getLinkVisualizer(tasklist[u], tasklist[v]);
	link_viz_p -> setLabel(why_depends_on(u,v));
      }
    }

    if (highlightCP)
      highlight_criticalpath();
        
    bridges::Bridges::setDataStructure(&g);
    
    auto end = std::chrono::system_clock::now();

    std::chrono::duration<double> elapsed_seconds = end-start;
 
    std::cout << "time to build viz: " << elapsed_seconds.count() << "s\n";
    
    bridges::Bridges::visualize();

  }
    
}


#endif
