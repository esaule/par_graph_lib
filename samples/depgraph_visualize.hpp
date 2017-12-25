#ifndef DEPGRAPH_VIZ_HPP
#define DEPGRAPH_VIZ_HPP

namespace depgraph {
  std::vector< std::list<int> > basic_graph;

  std::vector< std::list<int> > simplified_graph;

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
	      basic_graph[v].push_back(u);
	      //g.addEdge(*it, s, 1);
	    }
	  }
	}
      }
    }

    remove_transitive(basic_graph, simplified_graph);
  }

  bridges::GraphAdjList<string,int> g;


  //this algorithm works because the vertices are topo sorted
  void highlight_criticalpath() {
    std::vector<int> toplevel (simplified_graph.size(), 0);

    std::vector<int> predecessor (simplified_graph.size(), -1);
    
    int maxlevel = 0;
    int sinkvertex = -1;
    
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

    int x = sinkvertex;
    int prev = sinkvertex; //previous vertex in the reconstructed path (so the next according to the topological order
    while (x >= 0) {
      //x is on the critical path      

      //color x in red
      auto vert_x_p = g.getVertices().find(tasklist[x])->second;
      auto vert_viz_p = vert_x_p->getVisualizer();
      vert_viz_p->setColor(bridges::Color(255,0,0));
      
      //color the edge
      if (x != prev) {
	auto vert_prev_p = g.getVertices().find(tasklist[prev])->second;
	auto link_viz_p = vert_x_p->getLinkVisualizer(vert_prev_p);
	link_viz_p->setThickness(bridges::LinkVisualizer::DEFAULT_THICKNESS * 10.);
	link_viz_p->setColor(bridges::Color(255,0,0));
      }

      prev = x;
      x = predecessor[x];
    }
    
  }

  
  void visualize(){
    build_graph();
    
    bridges::Bridges::initialize(1, "esaule", "182708497087");

    g =  bridges::GraphAdjList<string,int>();
    
    for (int u=0; u<basic_graph.size(); ++u) {
      g.addVertex(tasklist[u], 0);
      
    }

    for (int u=0; u<basic_graph.size(); ++u) {
      for (auto v : basic_graph[u]) {
	g.addEdge(tasklist[u], tasklist[v], 1);
      }
    }
    
    bridges::Bridges::setDataStructure(&g);
    bridges::Bridges::visualize();
  }

  void visualize_simplified(){
    build_graph();
    
    bridges::Bridges::initialize(2, "esaule", "182708497087");

    g =  bridges::GraphAdjList<string,int>();

    for (int u=0; u<simplified_graph.size(); ++u) {
      g.addVertex(tasklist[u], 0);
    }
    
    for (int u=0; u<simplified_graph.size(); ++u) {
      for (auto v : simplified_graph[u]) {
	g.addEdge(tasklist[u], tasklist[v], 1);
      }
    }

    highlight_criticalpath();
    
    bridges::Bridges::setDataStructure(&g);
    bridges::Bridges::visualize();
  }
}


#endif
