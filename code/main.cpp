#include "interface.hpp"
using namespace std;

int main() {
    vector<Tourist*> tourists;
    vector<Bus*> buses;
    Graph map;

    loadTourists(tourists, buses);
    loadMap(map);

    interface(tourists, buses, map);
    
    exit(0);
}
