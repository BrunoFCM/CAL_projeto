#pragma once

#include <vector>
#include <unordered_set>

#include "Group.hpp"
#include "Graph.hpp"
#include "bus.hpp"

GroupSet getGroupSet(vector<Tourist *> tourists){
    GroupSet result;
    
    for(Tourist * tourist : tourists){
        result.insert(new Group(tourist));
    }

    return result;
}

void getCompatibilities(GroupSet & groups, const Graph &graph){
    for(auto i = groups.begin(); i != groups.end(); ++i){
        auto j = i; ++j;

        for(; j != groups.end(); ++j){
            (*i)->getCompatibility(*j, graph);
        }
    }
}

pair<int,int> getBestCombination(const GroupSet &groups){
    pair<int,int> result;
    double min = INF;

    for(auto i = groups.begin(); i != groups.end(); ++i){
        pair<int,double> bestCompatibility = (*i)->getBestPair();
        
        if(bestCompatibility.second < min){
            min = bestCompatibility.second;

            result.first = (*i)->getId();
            result.second = bestCompatibility.first;
        }
    }

    return result;
}

void infiniteCapacityOrganise(vector<Bus> &buses, GroupSet &groups){
    if(groups.size() == 1){
        Group group = **(groups.begin());
        group.setContentsTo(buses[0]);

        return;
    }

    pair<int,int> bestPair = getBestCombination(groups);

    auto group1 = groups.find(bestPair.first);
    auto group2 = groups.find(bestPair.second);

    Group * newGroup = new Group((*group1)->merge(**group2));

    if(buses.size() >= groups.size()){
        double baseDistance = ((*group1)->getAddedDistance() < (*group2)->getAddedDistance()) ? 
                                (*group2)->getAddedDistance() : (*group1)->getAddedDistance();

        if(baseDistance * 2 < newGroup->getAddedDistance()){
            int busIndex = 0;
            for(auto i = groups.begin(); i != groups.end(); ++i){
                (*i)->setContentsTo(buses[busIndex]);
                ++busIndex;
            }

            return;
        }
    }
    else{
        groups.erase(group1);
        groups.erase(group2);
        groups.insert(newGroup);

        infiniteCapacityOrganise(buses, groups);
    }
}

bool finiteCapacityOrganise(vector<Bus> &buses, GroupSet &groups){
    //TODO
    return false;
}
