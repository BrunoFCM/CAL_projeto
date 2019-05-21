#pragma once

#include "Group.hpp"
#include "tourist.hpp"

void Group::addTourist(Tourist * tourist){
    tourists.insert(tourist);

    vector<int> poi = tourist->getPOI;
    for(unsigned int i = 0; i < poi.size(); ++i){
        int poi_id = poi[i];
        auto point = POI.find(poi_id);
        if(point != POI.end){
            point->second++; 
        }
        else{
            POI.insert(make_pair(poi_id, 1));
        }
    }
}

void Group::merge(Group group){
    for(auto i = group.tourists.begin; i != group.tourists.end; ++i){
        if(tourists.find(*i) == tourists.end){
            addTourist(*i);
        }
    }
}

void Group::removeTourist(Tourist * tourist){
    auto i = tourists.find(tourist);

    if(i != tourists.end){
        tourists.erase(i);

        vector<int> poi = tourist->getPOI;
        for(unsigned int i = 0; i < poi.size(); ++i){
            int poi_id = poi[i];
            auto point = POI.find(poi_id);
            point->second--;
            if(point->second == 0){
                POI.erase(point);
            }
        }
    }
}

void Group::unmerge(Group group){
    for(auto i = group.tourists.begin; i != group.tourists.end; ++i){
        removeTourist(*i);
    }
}

double Group::getCompatibility(const Group &group) const{
    
    return 0;
}


