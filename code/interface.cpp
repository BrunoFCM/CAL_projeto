#include "interface.hpp"
using namespace std;

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
        cout << info << endl;
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
            cout << "|" << id << "|\t|" << cap << "|\n";
            bus = new Bus(id, cap);
            buses.push_back(bus);
        }
    }
    if (tourists.empty() || buses.empty()) {
        cout << "N TURISTS: " << tourists.size() << "\t N BUSES: " << buses.size();
        return false;
    }
    return true;
}

void add_turist(vector<Tourist*> tourists) {
    /* id,name,<list of pois>                     TURIST  */
    cout << "Write \"id,name,<list of pois>\" > ";
    Tourist* tourist;
    istringstream line;
    string info;

    getline(cin, info);
    line.str(info);
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
}

void add_bus(vector<Bus*> buses) {
    /* id,cap                                     BUS     */
    cout << "Write \"id,cap\" > ";
    Bus* bus;
    istringstream line;
    string info;

    getline(cin, info);
    line.str(info);
    int id;
    unsigned long long cap;

    getline(line, info, ',');
    id = stoi(info);
    getline(line, info, ',');
    cap = stoi(info);

    bus = new Bus(id, cap);
    buses.push_back(bus);
}

void check_turist(vector<Tourist*> tourists) {
    for (Tourist* t : tourists) {
        cout << "Id: " << setw(4) << t->getId() << "\t" << t->getName();
    }
}

void check_bus(vector<Bus*> buses) {
    for (Bus* b : buses) {
        cout << "Id: " << setw(4) << b->getId() << "\t" << setw(4)
             << b->getCap();
    }
}

void get_path() {
    cout << "1. Infinite Bus\n2.Infinite Buses\n3. Realist Buses\n";
    cout << "> ";
}

void interface(vector<Tourist*> tourists, vector<Bus*> buses) {
    int op;
    cout << "1. Add turist\n2.Add bus\n3. Check turist\n4.Check bus\n5. Get "
            "path\n";
    cout << "> ";
    cin >> op;

    switch (op) {
        case 1:
            add_turist(tourists);
            break;
        case 2:
            add_bus(buses);
            break;
        case 3:
            check_turist(tourists);
            break;
        case 4:
            check_bus(buses);
            break;
        case 5:
            get_path();
            break;
        default:
            break;
    }
}