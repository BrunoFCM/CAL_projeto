#include "interface.hpp"
using namespace std;

bool loadTourists(vector<Tourist*> &tourists, vector<Bus*> &buses) {
    ifstream input;
    input.open(INPUT_FILE);
    if (!input.is_open()) return false;
    istringstream line;
    string info;
    /* T,id,name,<list of pois>                     TOURIST  */
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
        info.clear();
        line.clear();
    }
    if (tourists.empty() || buses.empty()) {
        cout << "N TOURISTS: " << tourists.size()
             << "\t N BUSES: " << buses.size() << endl;
        return false;
    }
    return true;
}

void loadMap(Graph &map){
    map.getGraphInfo(NODES_FILE, EDGES_FILE);

    unordered_set<int> max_set;
    for(Vertex *v : map.getVertexSet()){
    	unordered_set<int> cur_set = map.getComponents(v->getId());
    	if(cur_set.size() > max_set.size()){
    		max_set = cur_set;
    	}
    }

    map.eraseNotConnected(max_set);
}

void add_tourist(vector<Tourist*> &tourists) {
    /* id,name,<list of pois>                     TOURIST  */
    cout << "Write \"id,name,<list of pois>\" \n> ";
    Tourist* tourist;
    istringstream line;
    string info;
    cin.ignore(1000000, '\n');
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

void add_bus(vector<Bus*> &buses) {
    /* id,cap                                     BUS     */
    cout << "Write \"id,cap\" \n> ";
    Bus* bus;
    istringstream line;
    string info;
    cin.ignore(1000000, '\n');
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

void check_tourist(vector<Tourist*> &tourists) {
    for (Tourist* t : tourists) {
        cout << "Id: " << setw(4) << t->getId() << "| Name: " << t->getName() << "\n";
    }
}

void check_bus(vector<Bus*> &buses) {
    for (Bus* b : buses) {
        cout << "Id: " << setw(4) << b->getId() << "| Capacity: " << setw(4) << b->getCap() << "\n";
    }
}

void get_path(vector<Tourist*> &tourists, vector<Bus*> &buses, Graph &map) {
	cout << "\nShowing path(s)\n\n";

	GraphViewer *gv = new GraphViewer(1000, 1000, false);
	gv->createWindow(1000, 1000);

	for(unsigned int i = 0; i < buses.size(); ++i){
		Bus* bus = buses[i];
		vector<int> poi = bus->getPOI();

		gv->defineEdgeColor("blue");
		switch(i % 13){
		case 0:	gv->defineVertexColor("BLUE");		break;
		case 1:	gv->defineVertexColor("RED");		break;
		case 2:	gv->defineVertexColor("PINK");		break;
		case 3:	gv->defineVertexColor("BLACK");		break;
		case 4:	gv->defineVertexColor("WHITE");		break;
		case 5:	gv->defineVertexColor("ORANGE");	break;
		case 6:	gv->defineVertexColor("YELLOW");	break;
		case 7:	gv->defineVertexColor("GREEN");		break;
		case 8:	gv->defineVertexColor("yellow");	break;
		case 9:	gv->defineVertexColor("yellow");	break;
		case 10:gv->defineVertexColor("yellow");	break;
		case 11:gv->defineVertexColor("yellow");	break;
		case 12:gv->defineVertexColor("yellow");	break;}

		if(poi.size() == 0){
			return;
		}

		vector<int> necessaryPoi = map.getCircularPath(poi);

	    map.displayPath(gv, necessaryPoi);
	}
}

void get_groups(vector<Tourist*> &tourists, vector<Bus*> &buses, Graph &map){
	unsigned int op;
    cout << "1. Infinite Bus\n2. Infinite Buses\n3. Realist Buses\n";
    cout << "> ";
    cin >> op;
    if (std::cin.fail()) { cin.clear(); cin.ignore(1000000, '\n'); return;}
    else{
    	switch(op){
			case 1:{
				noOrganizationSet(buses, tourists);
				break;
			}
			case 2:{
				Group::resetId();
				GroupSet gSet = getGroupSet(tourists);
				getCompatibilities(gSet, map);
				infiniteCapacityOrganize(buses, gSet);
				break;
			}
			case 3:{
				Group::resetId();
				GroupSet gSet = getGroupSet(tourists);
				getCompatibilities(gSet, map);
				finiteCapacityOrganize(buses, gSet);
				break;
			}
    	}
    }
}

void random_tourist(vector<Tourist*> &tourists, Graph &map){
	tourists.push_back(generateTourist(map));
	cout << "\nGenerated tourist\n\n";
}

void app_interface(vector<Tourist*> &tourists, vector<Bus*> &buses, Graph &map) {
    while(true){
        int op;
        cout << "====================\n";
        cout << "1. Add tourist\n2. Add bus\n3. Check tourist\n4. Check bus\n5. Get path\n6. Get groups\n7. Generate a random tourist\n0. Exit\n";
        cout << "> ";
        cin >> op;
        cout << "====================\n";
        switch (op) {
            case 1: add_tourist(tourists);          break;
            case 2: add_bus(buses);                 break;
            case 3: check_tourist(tourists);        break;
            case 4: check_bus(buses);               break;
            case 5: get_path(tourists, buses, map);      break;
            case 6: get_groups(tourists, buses, map);    break;
            case 7: random_tourist(tourists, map);		break;
            case 0: exit(0);
            default: cin.clear(); cin.ignore(1000000, '\n'); cout << "\n[ERROR: not an option]\n"; break;
        }
    }
}
