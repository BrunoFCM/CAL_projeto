#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include "bus.hpp"
#include "tourist.hpp"
#include "Graph.h"
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

int main() {
    vector<Tourist*> tourists;
    vector<Bus*> buses;
    loadTurists(tourists, buses);

    Graph<double> graph;
    graph.getGraphInfo();

    getchar();
    exit(0);
}