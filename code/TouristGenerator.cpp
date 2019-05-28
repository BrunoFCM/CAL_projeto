#include "TouristGenerator.hpp"
#include <time.h>


Tourist * generateTourist(const Graph &graph){
	Tourist * tourist = new Tourist();

	vertex_set_t vSet = graph.getVertexSet();

	for(unsigned int points = 0; points < 3; ++points){
		int poi = rand() % vSet.size();

		int counter = 0;
		for(auto i = vSet.begin(); i != vSet.end(); ++i){
			if(counter == poi){
					tourist->addPOI((*i)->getId());
					break;
			}
			++counter;
		}
	}

	return tourist;
}
