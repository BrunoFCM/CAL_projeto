#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include "Group.hpp"
#include "bus.hpp"
using namespace std;
#define INPUT_FILE  "input.txt"
#define NODES_FILE  "../T03_nodes_X_Y_Fafe.txt"
#define EDGES_FILE  "../T03_edges_Fafe.txt"

bool loadTourists(vector<Tourist*> &tourists, vector<Bus*> &buses);
void loadMap(Graph &map);

void add_tourist(vector<Tourist*> &tourists);
void add_bus(vector<Bus*> &buses);
void check_tourist(vector<Tourist*> &tourists);
void check_bus(vector<Bus*> &buses);
void get_path(vector<Tourist*> &tourists, vector<Bus*> &buses);
void get_groups(vector<Tourist*> &tourists, vector<Bus*> &buses);


void interface(vector<Tourist*> &tourists, vector<Bus*> &buses, Graph &map);