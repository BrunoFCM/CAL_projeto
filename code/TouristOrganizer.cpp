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

        if((*i)->getId() == 0){
			cout << "i fucked" << endl;
		}

        for(; j != groups.end(); ++j){
        	if((*j)->getId() == 0){
				cout << "j fucked" << endl;
			}
            (*i)->getCompatibility(*j, graph);
            cout << (*i)->getId() << "-" << (*j)->getId() << endl;
        }
    }
}

pair<int,int> getBestCombination(const GroupSet &groups){
    pair<int,int> result;
    double min = INF;

    for(auto i = groups.begin(); i != groups.end(); ++i){
        pair<int,double> bestCompatibility = (*i)->getBestPair();
        
        cout << "Found: " << (*i)->getId() << "-" << bestCompatibility.first << endl;

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

    cout << "Iteration\n"; fflush(stdout);
    pair<int,int> bestPair = getBestCombination(groups);

    cout << "Merged " << bestPair.first << " " << bestPair.second << "\n"; fflush(stdout);
    auto group1 = groups.find(bestPair.first);
    auto group2 = groups.find(bestPair.second);

    if(group1 == groups.end()){
    	cout << "FUCK1" << endl;
    }
    if(group2 == groups.end()){
		cout << "FUCK2" << endl;
	}

    fflush(stdout);
    Group mergedGroup = (*group1)->merge(**group2);
    Group * newGroup = new Group(mergedGroup);

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

	groups.erase(group1);
	groups.erase(group2);

	groups.insert(newGroup);

	for(auto i = groups.begin(); i != groups.end(); ++i){
		(*i)->removeCompatibility((*group1)->getId());
		(*i)->removeCompatibility((*group2)->getId());
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

