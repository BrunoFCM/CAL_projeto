#include "interface.hpp"
using namespace std;

int main() {
    vector<Tourist*> tourists;
    vector<Bus*> buses;
    loadTourists(tourists, buses);

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
    while (true) {
        interface(tourists, buses);
    }
    exit(0);
}
