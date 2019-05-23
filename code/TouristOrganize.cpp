#pragma once

#include <vector>

#include "Group.hpp"
#include "Graph.hpp"
#include "bus.hpp"

void getCompatibilities(vector<Group> & groups, const Graph &graph){
    for(unsigned int i = 0; i < groups.size(); ++i){
        for(unsigned int j = i + 1; j < groups.size(); ++j){
            groups[i].getCompatibility(groups[j], graph);
        }
    }
}

bool infiniteCapacityOrganise(vector<Bus> &buses, vector<Group> &groups){

}

bool finiteCapacityOrganise(vector<Bus> &buses, vector<Group> &groups){
    
}
