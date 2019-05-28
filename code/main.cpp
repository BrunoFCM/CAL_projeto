#include "interface.hpp"
using namespace std;

int main() {
    vector<Tourist*> tourists;
    vector<Bus*> buses;
    Graph map;

    loadTourists(tourists, buses);
    loadMap(map);
/*
    GraphViewer *gv = new GraphViewer(1000, 1000, false);

	gv->createWindow(2000, 2000);

	gv->defineEdgeColor("blue");
	gv->defineVertexColor("yellow");

	map.displayGraph(gv);
	gv->rearrange();
*/
    app_interface(tourists, buses, map);

    exit(0);
}
