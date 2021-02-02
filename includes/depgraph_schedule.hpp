#ifndef DEPGRAPH_SCHEDULE
#define DEPGRAPH_SCHEDULE



#include <SymbolCollection.h>
#include <Rectangle.h>
#include <Polyline.h>
#include <Polygon.h>
#include <Circle.h>
#include <Label.h>

namespace depgraph {


  void animate_listscheduling_inner(bridges::GraphAdjList<string,int>& dag, int nbproc,  bridges::Bridges& br) {

    double procheight = 50.;
    double procvspace = 10.;
    double proclabelxloc = -20.;
    double unittime_width = 15.;
    
    double maxtime = animate_toplevel(dag, -1, false);
    
    //set y-axis
    
    bridges::Polygon yaxis;
    yaxis.addPoint(0,0);
    yaxis.addPoint(0, nbproc*procheight+(nbproc-1)*procvspace);

    
    
    std::vector<bridges::Label> proclabels;
    for (int i=0; i<nbproc; ++i) {
      std::string l = "Proc " + std::to_string(i);
      bridges::Label lab (l);
      lab.setLocation(proclabelxloc, (i+.5)*procheight+(i-1)*procvspace);
      proclabels.push_back(lab);
    }

    std::vector<bridges::Label> tasklabels;
    std::vector<bridges::Rectangle> taskrect;

    auto add_gantt_task = [&](std::string name,
			      double timestart, double timeend,
			      int where) {
			    bridges::Rectangle r(timestart*unittime_width,(where)*(procheight+procvspace),
						 (timeend-timestart)*unittime_width, procheight);
			    maxtime = std::max(maxtime, timeend);
			    taskrect.push_back(r);

			    bridges::Label l (name);
			    l.setCenter((timestart+(timeend-timestart)/2)*unittime_width,
					(where)*procvspace + (where+0.5)*procheight);
			    tasklabels.push_back(l);
			  };


    auto push_gantt_chart
      = [&]() {
	  bridges::SymbolCollection gantt;
    
	  gantt.addSymbol(&yaxis);
    	  
	  // add all objects in collections
	  
	  for (int i=0; i<nbproc; ++i) {
	    gantt.addSymbol(&proclabels[i]);
	  }
	  
	  for (auto& r: taskrect) {
	    gantt.addSymbol(&r);
	  }
	  
	  for (auto& l: tasklabels) {
	    gantt.addSymbol(&l);
	  }
	  
	  gantt.setViewport(-40., (maxtime+2)*unittime_width, -20, nbproc*(procvspace+procheight));
	  
	  br.setDataStructure(gantt);
	  br.visualize();
	  
	};
    
    std::unordered_map<string, int> ready_time;
    auto ind = in_degree(dag);
    auto cmp = [](std::pair<int, string> a, std::pair<int, string> b){
		 return a > b;};
    std::priority_queue<std::pair<int, string>,
			std::vector<std::pair<int, string>>,
			decltype(cmp)> pqueue(cmp);

    std::vector<int> proc_ready;
    for (int i=0;i<nbproc; ++i)
      proc_ready.push_back(0);
    
    for (auto s: dag.keySet()) {
      ready_time[s] = 0;
      if (ind[s] == 0)
	pqueue.push(std::make_pair(ready_time[s], s));      
    }

    while (! pqueue.empty()) {
      //pop task
      auto task = pqueue.top().second;
      auto task_ready = pqueue.top().first;
      pqueue.pop();

      std::cout<<"scheduling "<<task<<"\n";
      
      //identify first processor ready
      int minproc=0;
      int minproc_time = proc_ready[0];
      for (int i=1; i<nbproc; ++i) {
	if (proc_ready[i] < minproc_time) {
	  minproc = i;
	  minproc_time = proc_ready[i];
	}
      }
      
      std::cout<<"minproc "<<minproc<< " available at "<<minproc_time<<"\n";
      
      
      //schedule task
      int sched_time = std::max(task_ready, minproc_time);
      int endtime = sched_time+dag.getVertexData(task);
      add_gantt_task(task, sched_time, endtime, minproc);

      //update processor
      proc_ready[minproc] = endtime;
      
      //update descendant
      for (auto edge : dag.outgoingEdgeSetOf(task)) {
	auto from = edge.from();
	auto to = edge.to();

	ready_time[to] = std::max(ready_time[to], endtime);
      	ind[to] --;
	if (ind[to] == 0)
	  pqueue.push(std::make_pair(ready_time[to], to));      

	std::cout<<"task "<<to<< " can't run before "<<ready_time[to]<<"\n";

	
      }
      push_gantt_chart();
    }

    push_gantt_chart();
  }
  
  
  void animate_listscheduling (bridges::GraphAdjList<string,int>& dag,
			       int nbproc,
			       int channel) {
    
    auto start = std::chrono::system_clock::now();

    std::string bridges_user;
    std::string bridges_apikey;

    get_bridges_account(bridges_user, bridges_apikey);
    
    bridges::Bridges br(channel, bridges_user, bridges_apikey);


    br.setDataStructure(dag);

    animate_listscheduling_inner(dag, nbproc, br);
    
  }
}

#endif
