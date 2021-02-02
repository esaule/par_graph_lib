#ifndef DEPGRAPH_TOPLEVEL
#define DEPGRAPH_TOPLEVEL

namespace depgraph {

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

    auto order = topological_order(dag);
    
    std::cout<<"order size: "<<order.size()<<"\n";
    
    std::unordered_map<string, int> level;
    std::unordered_map<string, int> maxparentlevel;

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

    auto updateparentlevel = [&](std::string vert, int newlevel) {
    			 maxparentlevel[vert] = newlevel;
    			 setlabel(vert);
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
    }

    for (auto v : order) {
      std::cout<<"v is "<<v<<"\n";
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
	
	updateparentlevel(to, std::max(maxparentlevel[to], level[v]));
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
