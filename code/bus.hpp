#pragma once

#include "tourist.hpp"
#include <unordered_set>
using namespace std;

class Bus {
    int id;
    unsigned long long cap;
    vector<Tourist*> passengers;
    unordered_set<int> POI;

   public:
    Bus(int id, unsigned long long cap);

    int getId() const;
    unsigned long long getCap() const;
    vector<Tourist*> getPassengers() const;
    vector<int> getPOI() const;
    void emptyBus();

    void addPassenger(Tourist* tourist);
};
