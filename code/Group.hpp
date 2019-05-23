#include "tourist.hpp"
#include "Graph.hpp"

#include <vector>
#include <map>
#include <unordered_set>

class Group {
    int group_id;
    static int incremented_id;

    std::unordered_set<int> POI;
    std::vector<Tourist *> tourists;

    std::map<int, double> compatibilities;

public:
    Group(Tourist * tourist);
    static void resetId();
    int getId();
    void addTourist(Tourist * tourist);
    void removeTourist(Tourist * tourist);
    Group merge(Group group);
    double getCompatibility(const Group &group) const;
    double getCompatibility(const Group &group, const Graph &graph) const;
};