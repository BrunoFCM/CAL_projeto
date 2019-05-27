#include "bus.hpp"
#include "tourist.hpp"

using namespace std;

Bus::Bus(int id, unsigned long long cap) {
    this->id = id;
    this->cap = cap;
}

int Bus::getId() const { return this->id; }
unsigned long long Bus::getCap() const { return this->cap; }
vector<Tourist*> Bus::getPassengers() const { return this->passengers; }

void Bus::addPassenger(Tourist* tourist) {
    this->passengers.push_back(tourist);
}