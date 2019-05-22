#include "Group.hpp"
#include "tourist.hpp"

void Group::addTourist(Tourist *tourist) {
    tourists.insert(tourist);

    vector<int> poi = tourist->getPOI();
    for (unsigned int i = 0; i < poi.size(); ++i) {
        POI.insert(poi[i]);
    }
}

Group Group::merge(Group group) {
    Group result;

    for (auto i = group.tourists.begin(); i != group.tourists.end(); ++i) {
        result.addTourist(*i);
    }

    for (auto i = tourists.begin(); i != tourists.end(); ++i) {
        result.addTourist(*i);
    }

    return result;
}
/*
double Group::getCompatibility(const Group &group) const {
    double compatibility = 0;

    return compatibility;
}*/
