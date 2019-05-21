#include "bus.hpp"

int Bus::getId() const { return this->id; }
unsigned long long Bus::getCap() const { return this->cap; }
vector<Tourist*> Bus::getPassengers() const { return this->passengers; }

void Bus::addPassenger(Tourist* tourist){
    this->passengers.push_back(tourist);
}