#include "interface.hpp"
using namespace std;

int main() {
    vector<Tourist*> tourists;
    vector<Bus*> buses;
    Graph map;

    loadTourists(tourists, buses);
    loadMap(map);

    interface(tourists, buses, map);
    
    /*
    GraphViewer *gv = new GraphViewer(1000, 1000, true);

	gv->createWindow(1000, 1000);

	gv->defineEdgeColor("blue");
	gv->defineVertexColor("yellow");
    g.getGraphInfo();
    std::vector<int> path;
    g.dijkstraShortestPath(1241362560);
    path = g.getPath(1241362560, 1241362657);
    cout << path.size() << endl;
    cout << "Hello" << endl;
    g.displayPath(gv, path);
    */
    
    exit(0);
}
