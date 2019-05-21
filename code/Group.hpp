#include "tourist.hpp"

#include <vector>
#include <map>

class Group {
    std::map<int, int> POI;
    vector<Tourist *> tourists;

public:
    void addTourist(Tourist * tourist);
    void removeTourist(Tourist * tourist);
    void merge(Group group);
    void unmerge(Group group);
    const double getCompatibility(Group group);
};