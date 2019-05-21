#include "tourist.hpp"

#include <vector>
#include <map>
#include <unordered_set>

class Group {
    std::map<int, int> POI;
    std::unordered_set<Tourist *> tourists;

public:
    void addTourist(Tourist * tourist);
    void removeTourist(Tourist * tourist);
    void merge(Group group);
    void unmerge(Group group);
    double getCompatibility(const Group &group) const;
};