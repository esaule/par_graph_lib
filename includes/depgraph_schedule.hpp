#ifndef DEPGRAPH_SCHEDULE
#define DEPGRAPH_SCHEDULE



#include <SymbolCollection.h>
#include <Rectangle.h>
#include <Polyline.h>
#include <Polygon.h>
#include <Circle.h>
#include <Label.h>

namespace depgraph {


  void animate_listscheduling_inner(bridges::GraphAdjList<string,int>& dag, int nbproc,
				    bool showready,
				    bridges::Bridges& brgantt,bridges::Bridges& brgraph) {

    reset_graphstyle(dag);
    
    
    double procheight = 50.;
    double procvspace = 10.;
    double proclabelxloc = -20.;
    double unittime_width = 15.;
    double tic_length = 2.;
    double timelabelyspacing = -10;
    double timelabelxspacing = -2;

    
    double maxtime = animate_toplevel(dag, -1, false);
    double totalwork = 0.;
    for (auto v : dag.keySet()) {
      totalwork += dag.getVertexData(v);
    }
    maxtime += totalwork/nbproc;
    
    //set axes
    
    bridges::Polyline yaxis;
    yaxis.addPoint(0,0);
    yaxis.addPoint(0, nbproc*procheight+(nbproc-1)*procvspace);

    bridges::Polyline xaxis;
    xaxis.addPoint(0, 0);
    xaxis.addPoint(maxtime*unittime_width, 0);

    bridges::Label timel ("time");
    timel.setLocation(maxtime*unittime_width+timelabelxspacing, 0+timelabelyspacing);
    
    std::vector<bridges::Polyline> tics;
    for (int i=0; i<(int)maxtime; ++i) {
      bridges::Polyline tic;
      tic.addPoint(i*unittime_width, 0);
      if (i%5 != 0)
	tic.addPoint(i*unittime_width, -tic_length);
      else
	if (i%10 != 0)
	  tic.addPoint(i*unittime_width, -tic_length*3);
	else
	  tic.addPoint(i*unittime_width, -tic_length*5);
      tics.push_back(tic);
    }
    
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
			    l.setStrokeColor(bridges::Color(255,255,255,0.));
			    tasklabels.push_back(l);
			  };


    auto push_gantt_chart
      = [&]() {
	  bridges::SymbolCollection gantt;

	  //axes
	  gantt.addSymbol(&yaxis);
	  gantt.addSymbol(&xaxis);

	  for (auto& t: tics) {
	    gantt.addSymbol(&t);
	  }

	  gantt.addSymbol(&timel);
	  
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
	  
	  brgantt.setDataStructure(gantt);
	  brgantt.visualize();
	  
	};

    auto push_graph
      = [&]() {
	  brgraph.setDataStructure(dag);
	  brgraph.visualize();
	};
    
    auto renderit = [&]() {
		      push_gantt_chart();
		      push_graph();
		    };

      
    std::unordered_map<string, int> ready_time;
    auto ind = in_degree(dag);
    auto cmp = [](std::pair<int, string> a, std::pair<int, string> b){
		 return a > b;};
    std::priority_queue<std::pair<int, string>,
			std::vector<std::pair<int, string>>,
			decltype(cmp)> pqueue(cmp);


    auto highlighttask
      = [&](std::string task) {
	  auto myver = dag.getVertex(task);
	  myver->setColor("red");
	};

    auto deactivatetask
      = [&](std::string task) {
	  auto myver = dag.getVertex(task);
	  myver->setColor("lightgrey");
	  myver->setLabel("");
	};

    auto deactivateedge
      = [&](std::string from, std::string to) {
	    dag.getLinkVisualizer(from, to)->setColor("lightgrey");
	};

    auto highlightedge
      = [&](std::string from, std::string to) {
	    dag.getLinkVisualizer(from, to)->setColor("red");
	};
    
    auto updatelabel
      = [&](std::string task) {
	  auto myver = dag.getVertex(task);
	  std::string lab = task
	    +"\nP = "+std::to_string(dag.getVertexData(task));
	  if (showready)
	    lab += "\nreadyTime = "+std::to_string(ready_time[task]); 
	  myver->setLabel(lab);
	};
    
    std::vector<int> proc_ready;
    for (int i=0;i<nbproc; ++i)
      proc_ready.push_back(0);
    
    for (auto s: dag.keySet()) {
      ready_time[s] = 0;
      if (ind[s] == 0)
	pqueue.push(std::make_pair(ready_time[s], s));      
      updatelabel(s);
    }

    renderit();
    
    while (! pqueue.empty()) {
      //pop task
      auto task = pqueue.top().second;
      auto task_ready = pqueue.top().first;
      pqueue.pop();

      highlighttask(task);
      updatelabel(task);
      renderit();
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

      renderit();
      
      //update descendant
      for (auto edge : dag.outgoingEdgeSetOf(task)) {
	auto from = edge.from();
	auto to = edge.to();

	ready_time[to] = std::max(ready_time[to], endtime);
      	ind[to] --;
	if (ind[to] == 0)
	  pqueue.push(std::make_pair(ready_time[to], to));      

	highlightedge(from, to);
	
	updatelabel(to);
	renderit();
	
	deactivateedge(from, to);
	std::cout<<"task "<<to<< " can't run before "<<ready_time[to]<<"\n";
	
	
      }
      deactivatetask(task);
      renderit();

    }

    renderit();
  }
  
  
  void animate_listscheduling (bridges::GraphAdjList<string,int>& dag,
			       int nbproc,
			       int channelgantt, int channelgraph, bool showready = true) {
    
    auto start = std::chrono::system_clock::now();

    std::string bridges_user;
    std::string bridges_apikey;

    get_bridges_account(bridges_user, bridges_apikey);
    
    bridges::Bridges brgantt(channelgantt, bridges_user, bridges_apikey);
    bridges::Bridges brgraph(channelgraph, bridges_user, bridges_apikey);



    animate_listscheduling_inner(dag, nbproc, showready, brgantt, brgraph);
    
  }
}

#endif
