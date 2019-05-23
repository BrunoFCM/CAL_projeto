#include "tourist.hpp"
#include "Graph.hpp"

#include <vector>
#include <map>
#include <unordered_set>

class Group {
    std::unordered_set<int> POI;
    std::unordered_set<Tourist *> tourists;

    static vector<Vertex *> vertexReference;
public:
    void addTourist(Tourist * tourist);
    void removeTourist(Tourist * tourist);
    Group merge(Group group);
    double getCompatibility(const Group &group) const;
};