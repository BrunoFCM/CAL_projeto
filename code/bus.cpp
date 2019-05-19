#include "bus.hpp"

int Bus::getId() { return this->id; }
unsigned long long Bus::getCap() { return this->cap; }
vector<Tourist*> Bus::getPassengers() { return this->passengers; }

void Bus::addPassenger(Tourist* tourist){
    this->passengers.push_back(tourist);
}