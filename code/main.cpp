#include <fstream>
#include <iostream>
#include <string>
#include "bus.hpp"
#include "tourist.hpp"

#define INPUT_FILE "input.txt"

bool loadTurists() {
    ifstream input; input.open(INPUT_FILE);
    string line;
    /* T,id,name,<list of pois>                     TURIST  */
    /* B,id,cap                                     BUS     */
    while(getline(input, line)){
        if(line.at(0) == 'T'){

        }
    }
}

int main() { return 0; }