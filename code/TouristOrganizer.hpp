#pragma once

#include <vector>

#include "Group.hpp"
#include "Graph.hpp"
#include "bus.hpp"

GroupSet getGroupSet(vector<Tourist *> tourists);

void getCompatibilities(GroupSet & groups, const Graph &graph);

void infiniteCapacityOrganise(vector<Bus> &buses, GroupSet &groups);

bool finiteCapacityOrganise(vector<Bus> &buses, GroupSet &groups);
