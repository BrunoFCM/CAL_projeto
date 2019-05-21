#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include "bus.hpp"
#include "tourist.hpp"

#define INPUT_FILE "input.txt"

bool loadTurists() {
    ifstream input; input.open(INPUT_FILE);
    istringstream line; string info;
    /* T,id,name,<list of pois>                     TURIST  */
    /* B,id,cap                                     BUS     */

    vector<Tourist*> tourists;
    vector<Bus*> buses;
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

        } else if (info == "B") {
            int id;
            unsigned long long cap;
            getline(line, info, ',');
            id = stoi(info);
            getline(line, info, ',');
            cap = stoi(info);

            bus = new Bus(id, cap);
        }
    }
}

int main() { return 0; }