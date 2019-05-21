#pragma once

#include <vector>
#include <string>
using namespace std;

class Tourist {
    int id;
    string name;
    vector<int> points_of_interest;

    public:
     int getId();
     string getName();
     vector<int> getPOI();

     void addPOI(int poi_id);
};