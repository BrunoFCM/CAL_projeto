#include "tourist.hpp"

using namespace std;

class Bus {
    int id;
    unsigned long long cap;
    vector<Tourist*> passengers;
    /*vector<int> arestas;           arestas que o autocarro passa*/

   public:
    int getId();
    unsigned long long getCap();
    vector<Tourist*> getPassengers();

    void addPassenger(Tourist* tourist);
};