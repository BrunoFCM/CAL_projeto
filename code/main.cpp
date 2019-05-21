#include <fstream>
#include <iostream>
#include <string>
#include "bus.hpp"
#include "tourist.hpp"

#define TURISTA_FILE "turista.txt"

bool loadTurists() {
    ifstream input; input.open(TURISTA_FILE);
    string line;
    /*T id name <list of pois>*/
    while(getline(input, line)){
        
    }
}

int main() { return 0; }