#include "tourist.hpp"
<<<<<<< HEAD
=======
using namespace std;

Tourist::Tourist(int id, string name) {
    this->id = id;
    this->name = name;
}
>>>>>>> 7e4ef0c1faece92e557355d17b37d5c1ef55ea64

int Tourist::getId() { return this->id; }
string Tourist::getName() { return this->name; }
vector<int> Tourist::getPOI() { return this->points_of_interest; }
void Tourist::addPOI(int poi_id) { this->points_of_interest.push_back(poi_id); }