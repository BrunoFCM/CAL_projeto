#pragma once

#include <vector>
#include <queue>

#include "Group.hpp"
#include "Graph.hpp"
#include "bus.hpp"

typedef struct combination{
    int first;
    int second;
    double value;
} combination_t;

class combinationCompare {
public:
	bool operator()(const combination_t &c1, const combination_t &c2) const {
		return c1.value < c2.value;
	}
};

typedef priority_queue<combination_t, std::vector<combination_t>, combinationCompare> CombinationQueue;

GroupSet getGroupSet(vector<Tourist *> tourists);

void getCompatibilities(GroupSet & groups, const Graph &graph);

pair<int,int> getBestCombination(const GroupSet &groups);

void noOrganizationSet(vector<Bus*> &buses, vector<Tourist *> &tourists);

void infiniteCapacityOrganize(vector<Bus*> &buses, GroupSet &groups);

CombinationQueue getCombinationOrder(const GroupSet &groups);

bool finiteCapacityOrganize(vector<Bus*> &buses, GroupSet &groups);
