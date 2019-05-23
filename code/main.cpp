#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include "bus.hpp"
#include "Group.hpp"
using namespace std;

#define INPUT_FILE "input.txt"

bool loadTurists(vector<Tourist*> tourists, vector<Bus*> buses) {
    ifstream input;
    input.open(INPUT_FILE);
    if (!input.is_open()) return false;
    istringstream line;
    string info;
    /* T,id,name,<list of pois>                     TURIST  */
    /* B,id,cap                                     BUS     */

    Tourist* tourist;
    Bus* bus;

    while (getline(input, info)) {
        line.str(info);
        getline(line, info, ',');
        if (info == "T") {
            int id;
            string name;
            getline(line, info, ',');
            id = stoi(info);
            getline(line, info, ',');
            name = info;
            tourist = new Tourist(id, name);

            while (getline(line, info, ',')) {
                int poi = stoi(info);
                tourist->addPOI(poi);
            }

            tourists.push_back(tourist);
        } else if (info == "B") {
            int id;
            unsigned long long cap;

            getline(line, info, ',');
            id = stoi(info);
            getline(line, info, ',');
            cap = stoi(info);

            bus = new Bus(id, cap);
            buses.push_back(bus);
        }
    }
    if (tourists.empty() || buses.empty()) return false;
    return true;
}

int main() {/*
    vector<Tourist*> tourists;
    vector<Bus*> buses;
    loadTurists(tourists, buses);*/

    Graph g;
    g.addVertex(0, 0, 0);
    g.addVertex(1, 0, 0);
    g.addVertex(2, 0, 0);
    g.addVertex(3, 0, 0);
    g.addVertex(4, 0, 0);

    g.addEdge(0, 0, 2); 
    g.addEdge(1, 2, 1); 
    g.addEdge(2, 1, 0); 
    g.addEdge(3, 0, 3); 
    g.addEdge(4, 0, 4);

    g.eraseNotConnected(0);

    //graph.getGraphInfo();
    exit(0);
}
