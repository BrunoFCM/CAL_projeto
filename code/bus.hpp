#include "tourist.hpp"
using namespace std;

class Bus {
    int id;
    unsigned long long cap;
    vector<Tourist*> passengers;
    /*vector<int> arestas;           arestas que o autocarro passa*/

   public:
    Bus(int id, unsigned long long cap);

    int getId() const;
    unsigned long long getCap() const;
    vector<Tourist*> getPassengers() const;

    void addPassenger(Tourist* tourist);
};