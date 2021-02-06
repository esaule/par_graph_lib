#ifndef DEPGRAPH_TOPLEVEL
#define DEPGRAPH_TOPLEVEL

namespace depgraph {

  void reset_graphstyle (bridges::GraphAdjList<string,int> & graph) {
    for (auto vert: graph.keySet()) {
      graph.getVertex(vert)->setColor("steelblue");
      graph.getVertex(vert)->setLabel(vert);
      
      for (auto edge : graph.outgoingEdgeSetOf(vert)) {
	auto from = edge.from();
	auto to = edge.to();
	graph.getLinkVisualizer(from, to) -> setColor("steelblue");
      }
    }
  }
  
  std::unordered_map<string, int> in_degree (bridges::GraphAdjList<string,int> const & graph){
    std::unordered_map<string, int> in_d;
    
    for (auto vert: graph.keySet()) {
      in_d[vert] = 0;
    }

    for (auto vert: graph.keySet()) {
      for (auto edge : graph.outgoingEdgeSetOf(vert)) {
	auto from = edge.from();
	auto to = edge.to();
	in_d[to] ++;
      }
    }

    return in_d;
  }
  
  std::vector<string> topological_order(bridges::GraphAdjList<string,int>& dag) {
    std::vector<string> order;

    auto indeg = in_degree(dag);

    std::queue<string> q;

    for (auto vert: dag.keySet()) {
      if (indeg[vert] == 0)
	q.push(vert);
    }

    while (! q.empty()) {
      auto current = q.front();
      //std::cout<<current<<"\n";
      order.push_back(current);
      
      for (auto edge : dag.outgoingEdgeSetOf(current)) {
	auto from = edge.from();
	auto to = edge.to();
	indeg[to] --;
	if (indeg[to] == 0) {
	  q.push(to);
	}
      }
      
      q.pop();
    }

    return order;
  }
  
  int animate_toplevel_inner(bridges::GraphAdjList<string,int>& dag,
			     bridges::Bridges& br,
			     bool render) {

    reset_graphstyle(dag);
    
    auto order = topological_order(dag);
    
    std::cout<<"order size: "<<order.size()<<"\n";
    
    std::unordered_map<string, int> level;
    std::unordered_map<string, int> maxparentlevel;
    std::unordered_map<string, string> parent;

    int maxlevel = 0;
    
    auto setlabel = [&](std::string vert) {
    		      if (render) {
    			auto myver = dag.getVertex(vert);
    			myver->setLabel(vert
    					+"\nP = "+std::to_string(dag.getVertexData(vert))
    					+"\nMaxParentLevel="+std::to_string(maxparentlevel[vert])
    					+"\nLevel = "+std::to_string(level[vert]));
    		      }
    		    };


    auto updatelevel = [&](std::string vert, int newlevel) {
    			 level[vert] = newlevel;
    			 maxlevel = std::max(maxlevel, newlevel);
    			 setlabel(vert);
    		    };

    auto updateparentlevel = [&](std::string from, std::string to) {
			       if (maxparentlevel[to] < level[from]) {
				 parent[to] = from;
				 maxparentlevel[to] = level[from];
				 setlabel(to);
			       }
			     };
    
    auto deactivateedge = [&](std::string from, std::string to) {
    			    if (render) {
    			      dag.getLinkVisualizer(from, to)->setColor("lightgrey");
    			    }
    			 };

    auto highlightedge = [&](std::string from, std::string to) {
    			   if (render) {
    			     std::cout<<"from "<<from<<" to "<<to<<"\n"<<std::flush; 
    			     dag.getLinkVisualizer(from, to)->setColor("red");
    			   }
    			 };


    auto highlightvert = [&](std::string vertid) {
    			   if (render) {
    			     auto myver = dag.getVertex(vertid);
    			     myver->setColor("red");
    			   }
    			 };


    auto deactivatevert = [&](std::string vertid) {
    			    if (render) {
    			      auto myver = dag.getVertex(vertid);
    			      myver->setColor("lightgrey");
    			    }
    			  };
    
    for (auto v : order) {
      level[v] = 0;
      maxparentlevel[v] = 0;
      setlabel(v);
      parent[v] = v;
    }

    for (auto v : order) {
      std::cout<<"v is "<<v<<"\n";
    }

    if (render) {
      br.visualize();
    }
    
    for (auto v : order) {
      std::cout<<v<<"\n";
      highlightvert(v);
      
      updatelevel(v, maxparentlevel[v] + dag.getVertexData(v));
      if (render) {
	br.visualize();
      }

      for (auto edge : dag.outgoingEdgeSetOf(v)) {
	auto from = edge.from();
	auto to = edge.to();

	std::cout<<"edge: "<<from<<" "<<to<<"\n";
	
	updateparentlevel(from, to);
	highlightedge(from, to);
	
	if (render) {
	  br.visualize();
	}
	deactivateedge(from, to);
      }
      
      if (render)  {
	br.visualize();
      }
      
      deactivatevert(v);
    }
    std::cout<<"algo done\n";

    if (render) {
      br.visualize();//to show the final deactivation
    }


    //tracing critical path 
    maxlevel = -1;
    std::string maxtask;
    for (auto v: order) {
      if (level[v] > maxlevel) {
	maxlevel = level[v];
	maxtask = v;
      }
    }

    std::string prevtask;
    highlightvert(maxtask);
    if (render) {
      br.visualize();
    }
    
    while (maxtask != parent[maxtask]) {
      prevtask = maxtask;
      maxtask = parent[maxtask];
      highlightedge(maxtask, prevtask);
      highlightvert(maxtask);
      if (render) {
	br.visualize();
      }
      
    }

    return maxlevel;
  }
  
  int animate_toplevel (bridges::GraphAdjList<string, int>& dag,
			int channel,
			bool render = true) {
    std::string bridges_user;
    std::string bridges_apikey;

    get_bridges_account(bridges_user, bridges_apikey);
    
    bridges::Bridges br(channel, bridges_user, bridges_apikey);

    if (render)
      br.setDataStructure(dag);

    return animate_toplevel_inner(dag, br, render);
    
  }
}

#endif
