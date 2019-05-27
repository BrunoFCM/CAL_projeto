#include "Group.hpp"
#include "Graph.hpp"
#include "tourist.hpp"

#include <map>

int Group::incremented_id = 0;

Group::Group(){
    group_id = ++incremented_id;
}

Group::Group(int id){
    group_id = id;
}

Group::Group(Tourist * tourist){
    group_id = ++incremented_id;

    if(tourist == NULL){
        return;
    }

    tourists.push_back(tourist);

    vector<int> touristPoi = tourist->getPOI();
    for(unsigned int i = 0; i < touristPoi.size(); ++i){
        POI.insert(touristPoi[i]);
    }
}
    
void Group::resetId(){
    incremented_id = 0;
}

int Group::getId() const{
    return group_id;
}

void Group::setAddedDistance(const Graph &graph){

    double addedDistance = 0;
    int comparisons;

    for(auto i = POI.begin(); i != POI.end(); ++i){
        Vertex * iVertex = graph.findVertex(*i);

        auto j = i;
        ++j;
        for(; j != POI.end(); ++j){
            Vertex * jVertex = graph.findVertex(*j);

            addedDistance += iVertex->distanceTo(jVertex);
            comparisons++;
        }
    }

    //Setting added distance to the group
    this->addedDistance = addedDistance / comparisons * POI.size();
}

double Group::getAddedDistance() const{
    return addedDistance;
}

Group Group::merge(const Group &group) const {
    Group result;

    for (unsigned int i = 0; i < group.tourists.size(); ++i) {
        result.tourists.push_back(group.tourists[i]);
    }

    for (unsigned int i = 0; i < tourists.size(); ++i) {
        result.tourists.push_back(tourists[i]);
    }

    for (auto i = compatibilities.begin(); i != compatibilities.end(); ++i){
        result.compatibilities.insert(*i);
    }

    for (auto i = group.compatibilities.begin(); i != group.compatibilities.end(); ++i){
        auto duplicate = result.compatibilities.find(i->first);

        if(duplicate != result.compatibilities.end()){
            if(i->second < duplicate->second){
                duplicate->second = i->second;
            }
        }
    }

    auto mergeCompatibility = result.compatibilities.find(group_id);
    double newDistance = group_id < group.group_id ? group.group_id : group_id;

    result.addedDistance = mergeCompatibility->second + newDistance;

    for (auto i = POI.begin(); i != POI.end(); ++i){
        result.POI.insert(*i);
    }

    for (auto i = group.POI.begin(); i != group.POI.end(); ++i){
        result.POI.insert(*i);
    }

    

    return result;
}

double Group::getCompatibility(const Group * group) const{
    auto found = compatibilities.find(group->group_id);

    if(found != compatibilities.end()){
        return found->second;
    }
    else{
        return 0;
    }
}

double Group::getCompatibility(Group * group, const Graph &graph) {
    double compatibilityA = 0, compatibilityB = 0;

    if(group_id == group->group_id){
        return compatibilityA;
    }

    auto found = compatibilities.find(group->group_id);

    if(found != compatibilities.end()){
        return found->second;
    }
    else{
        for(auto i = POI.begin(); i != POI.end(); ++i){
            double min = INF;

            Vertex * iVertex = graph.findVertex(*i);
            if(iVertex == NULL){
                continue;
            }

            for(auto j = group->POI.begin(); j != group->POI.end(); ++j){
                Vertex * jVertex = graph.findVertex(*j);
                if(jVertex == NULL){
                    continue;
                }

                double distance = iVertex->distanceTo(jVertex);
        
                if(distance < min){
                    min = distance;

                    if(distance == 0){
                        break;
                    }
                }
            }

            compatibilityA += min;
        }

        for(auto i = POI.begin(); i != POI.end(); ++i){
            double min = INF;

            Vertex * iVertex = graph.findVertex(*i);
            if(iVertex == NULL){
                continue;
            }

            for(auto j = group->POI.begin(); j != group->POI.end(); ++j){
                Vertex * jVertex = graph.findVertex(*j);
                if(jVertex == NULL){
                    continue;
                }

                double distance = iVertex->distanceTo(jVertex);
        
                if(distance < min){
                    min = distance;

                    if(distance == 0){
                        break;
                    }
                }
            }

            compatibilityB += min;
        }
    }

    double compatibility = (compatibilityA < compatibilityB) ? compatibilityA : compatibilityB;

    compatibilities.insert(std::pair<int,double>(group->getId(),compatibility));
    if(compatibility < bestPair.second){
        bestPair.first = group->group_id;
        bestPair.second = compatibility;
    }
    
    group->compatibilities.insert(std::pair<int,double>(this->getId(),compatibility));
    if(compatibility < group->bestPair.second){
        group->bestPair.first = group_id;
        group->bestPair.second = compatibility;
    }

    return compatibility;
}

pair<int,double> Group::getBestPair() const{
    return bestPair;
}



std::unordered_set<Group *, HashByGroupId, GroupEqual>::iterator GroupSet::find(int id){
    Group * dummy = new Group(id);

    return find(dummy);
}

void Group::setContentsTo(Bus &bus){
    for(unsigned int i = 0; i < tourists.size(); ++i)
    {
        bus.addPassenger(tourists[i]);
    }
}
