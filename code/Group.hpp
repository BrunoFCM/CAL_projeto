#pragma once

#include "tourist.hpp"
#include "Graph.hpp"
#include "bus.hpp"

#include <vector>
#include <map>
#include <unordered_set>

class GroupSet;

class Group {
    int group_id;
    static int incremented_id;

    std::unordered_set<int> POI;
    std::vector<Tourist *> tourists;

    std::map<int, double> compatibilities;
    pair<int,double> bestPair;

    double addedDistance;

public:
    Group();
    Group(int id);
    Group(Tourist * tourist);
    static void resetId();
    int getId() const;
    void setAddedDistance(const Graph &graph);
    double getAddedDistance() const;
    Group merge(const Group &group, GroupSet &groups) const;
    double getCompatibility(const Group * group) const;
    double getCompatibility(Group * group, const Graph &graph) ;
    pair<int,double> getBestPair();
    void setContentsTo(Bus *bus);
    void removeCompatibility(int id);
    void addCompatibility(int id, double dist);
};

class GroupEqual {
public:
	bool operator()(const Group * g1, const Group * g2) const {
		return g1->getId() == g2->getId();
	}
};

class HashByGroupId {
public:
	size_t operator()(Group* const& g) const {
		int id = g->getId();
		return std::hash<int>()(id);
	}
};

class GroupSet {
public:
    std::unordered_set<Group *, HashByGroupId, GroupEqual> groups;
    std::unordered_set<Group *, HashByGroupId, GroupEqual>::iterator find(Group * group) {return groups.find(group);}; 
    std::unordered_set<Group *, HashByGroupId, GroupEqual>::iterator find(int id);
    std::unordered_set<Group *, HashByGroupId, GroupEqual>::const_iterator begin() const {return groups.begin();}
    std::unordered_set<Group *, HashByGroupId, GroupEqual>::const_iterator end() const {return groups.end();}
    void insert(Group * group) {groups.insert(group);}
    void erase(std::unordered_set<Group *, HashByGroupId, GroupEqual>::iterator it) {groups.erase(it);}
    size_t size() const {return groups.size();}

    ~GroupSet(){
        for(Group * group : groups){
            delete(group);
        }
    }
};
