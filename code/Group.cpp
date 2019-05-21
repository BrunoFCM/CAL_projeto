#pragma once

#include "Group.hpp"
#include "tourist.hpp"

void Group::addTourist(Tourist * tourist){
    for(unsigned int i = 0; i < tourists.size(); ++i){
        if(tourist == tourists[i]){
            return;
        }
    }

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
    for(auto i = group.POI.begin; i != group.POI.end ; ++i){
        addTourist(group.tourists[i]);
    }
}

void Group::removeTourist(Tourist * tourist){
    for(unsigned int i = 0; i < tourists.size(); ++i){
        if(tourist == tourists[i]){
            tourists.erase(tourists.begin + i);

            vector<int> poi = tourist->getPOI;
            for(unsigned int i = 0; i < poi.size(); ++i){
                int poi_id = poi[i];
                auto point = POI.find(poi_id);
                point->second--;
                if(point->second == 0){
                    POI.erase(point);
                }
            }

            break;
        }
    }
}

void Group::unmerge(Group group){
    for(unsigned int i = 0; i < group.tourists.size(); ++i){
        removeTourist(group.tourists[i]);
    }
}

