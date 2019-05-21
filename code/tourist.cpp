#include "tourist.hpp"

Tourist::Tourist(int id, string name) {
    this->id = id;
    this->name = name;
}

int Tourist::getId() { return this->id; }
string Tourist::getName() { return this->name; }
vector<int> Tourist::getPOI() { return this->points_of_interest; }
void Tourist::addPOI(int poi_id) { this->points_of_interest.push_back(poi_id); }