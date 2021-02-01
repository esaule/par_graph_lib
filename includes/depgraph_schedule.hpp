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
    double unittime_width = 5.;
    
    double maxtime = 1.;
    
    bridges::SymbolCollection gantt;

    //set y-axis
    
    bridges::Polygon yaxis;
    yaxis.addPoint(0,0);
    yaxis.addPoint(0, nbproc*procheight+(nbproc-1)*procvspace);

    gantt.addSymbol(&yaxis);
    
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


    add_gantt_task("mytask", 0, 10, 1);
    
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
