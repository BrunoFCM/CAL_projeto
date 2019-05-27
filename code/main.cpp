#include "interface.hpp"
using namespace std;

int main() {
    cout << "START\n";
    vector<Tourist*> tourists;
    vector<Bus*> buses;
    if (!loadTurists(tourists, buses)) exit(1);

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
    cout << "\n\nINTERFACE\n\n";
    interface(tourists, buses);

    exit(0);
}
