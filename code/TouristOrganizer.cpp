#include <vector>
#include <unordered_set>
#include <queue>

#include "Group.hpp"
#include "Graph.hpp"
#include "bus.hpp"
#include "TouristOrganizer.hpp"

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
    	cout << (*i)->getId() << "id" << endl;
        pair<int,double> bestCompatibility = (*i)->getBestPair();

        if(bestCompatibility.second < min){
            min = bestCompatibility.second;

            result.first = (*i)->getId();
            result.second = bestCompatibility.first;
        }
    }

    return result;
}

void noOrganizationSet(vector<Bus*> &buses, vector<Tourist *> &tourists){
    for(unsigned int i = 0; i < tourists.size(); ++i){
        buses[0]->addPassenger(tourists[i]);
    }
}

void infiniteCapacityOrganize(vector<Bus*> &buses, GroupSet &groups){
    if(groups.size() == 1){
        Group group = **(groups.begin());
        group.setContentsTo(buses[0]);

        return;
    }

    pair<int,int> bestPair = getBestCombination(groups);

    auto group1 = groups.find(bestPair.first);
    auto group2 = groups.find(bestPair.second);

    cout << bestPair.first << "-" << bestPair.second << endl;

    if(group1 == groups.end()){
    	cout << "FUCK1" << endl;
    }
    if(group2 == groups.end()){
		cout << "FUCK2" << endl;
	}

    Group * g1 = *group1;
    Group * g2 = *group2;

    fflush(stdout);
    Group mergedGroup = (*group1)->merge(**group2, groups);
    Group * newGroup = new Group(mergedGroup);

    cout << (*group1)->getId() << " " << (*group2)->getId() << endl;

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

	groups.erase(groups.find(g1));
	groups.erase(groups.find(g2));

	groups.insert(newGroup);

	for(auto i = groups.begin(); i != groups.end(); ++i){
		cout << "Removing " <<  g1->getId() << " from " << (*i)->getId() << endl;
		(*i)->removeCompatibility(g1->getId());
		cout << "Removing " <<  g2->getId() << " from " << (*i)->getId() << endl;
		(*i)->removeCompatibility(g2->getId());
	}


	infiniteCapacityOrganize(buses, groups);

}

CombinationQueue getCombinationOrder(const GroupSet &groups){
    CombinationQueue queue;

    for(auto i = groups.begin(); i != groups.end(); ++i){        
        auto j = i;
        ++j;

        for(; j != groups.end(); ++j){
            double value = (*i)->getCompatibility(*j);
            int first = (*i)->getId();
            int second = (*j)->getId();

            combination_t combination = {first, second, value};
            queue.push(combination);
        }
    }

    return queue;
}

//This function assumes that |tourists| <= sum(busCapacity)
bool finiteCapacityOrganize(vector<Bus*> &buses, GroupSet &groups){
    if(groups.size() == 1){
        Group group = **(groups.begin());
        group.setContentsTo(buses[0]);

        return true;
    }

    CombinationQueue combinations = getCombinationOrder(groups);
    while(combinations.size() != 0)
    {
        combination_t combine = combinations.top();
        combinations.pop();

        auto group1 = groups.find(combine.first);
        auto group2 = groups.find(combine.second);

        Group * newGroup = new Group((*group1)->merge(**group2, groups));

        if(buses.size() >= groups.size()){
            double baseDistance = ((*group1)->getAddedDistance() < (*group2)->getAddedDistance()) ? 
                                    (*group2)->getAddedDistance() : (*group1)->getAddedDistance();

            if(baseDistance * 2 < newGroup->getAddedDistance()){
                int busIndex = 0;
                for(auto i = groups.begin(); i != groups.end(); ++i){
                    (*i)->setContentsTo(buses[busIndex]);
                    ++busIndex;
                }

                return true;
            }
        }
        Group * g1 = *group1;
        Group * g2 = *group2;
        groups.erase(group1);
        groups.erase(group2);
        groups.insert(newGroup);

        if(finiteCapacityOrganize(buses, groups)){
            return true;
        }
        else{
            //reseting set state
            groups.erase(groups.find(newGroup));
            delete(newGroup);
            groups.insert(g1);
            groups.insert(g2);
        }
    }

    return false;
}

