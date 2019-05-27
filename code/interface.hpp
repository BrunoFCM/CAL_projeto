#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include "Group.hpp"
#include "bus.hpp"
using namespace std;
#define INPUT_FILE "input.txt"

bool loadTourists(vector<Tourist*> &tourists, vector<Bus*> &buses);
void add_tourist(vector<Tourist*> &tourists);
void add_bus(vector<Bus*> &buses);
void check_tourist(vector<Tourist*> &tourists);
void check_bus(vector<Bus*> &buses);
void get_path();
void interface(vector<Tourist*> &tourists, vector<Bus*> &buses);