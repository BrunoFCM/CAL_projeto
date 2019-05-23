#include "Group.hpp"
#include "Graph.hpp"
#include "tourist.hpp"

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

int Group::getId(){
    return group_id;
}

Group Group::merge(Group group) {
    Group result(NULL);

    for (unsigned int i = 0; i < group.tourists.size(); ++i) {
        result.tourists.push_back(group.tourists[i]);
    }

    for (unsigned int i = 0; i < tourists.size(); ++i) {
        result.tourists.push_back(tourists[i]);
    }

    for (auto i = POI.begin(); i != POI.end(); ++i){
        result.POI.insert(*i);
    }

    for (auto i = group.POI.begin(); i != group.POI.end(); ++i){
        result.POI.insert(*i);
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
        else{
            result.compatibilities.insert(*i);
        }
    }

    return result;
}

double Group::getCompatibility(const Group &group) const{
    auto found = compatibilities.find(group.group_id);

    if(found != compatibilities.end()){
        return found->second;
    }
    else{
        return INF;
    }
}

double Group::getCompatibility(const Group &group, const Graph &graph) const {
    double compatibility = 0;

    auto found = compatibilities.find(group.group_id);

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

            for(auto j = group.POI.begin(); j != group.POI.end(); ++j){
                Vertex * jVertex = graph.findVertex(*j);
                if(jVertex == NULL){
                    continue;
                }

                double distance = iVertex->distanceTo(jVertex);
        
                if(distance < min){
                    min = distance;

                    if(distance <= 0){
                        break;
                    }
                }
            }

            compatibility += min;
        }
    }

    return compatibility;
}
