#include "Graph.h"
using namespace std;

/******************GRAPH*********************/
int Graph::getNumVertex() const {
	return vertexSet.size();
}

std::unordered_set<Vertex *, HashById, VertexEqual> Graph::getVertexSet() const {
	return vertexSet;
}

/*
 * Auxiliary function to find a vertex with a given content.
 */
Vertex * Graph::findVertex(const int &in) const {
	auto found = vertexSet.find(new Vertex(in, 0, 0));
	if(found != vertexSet.end()){
		return *found;
	}

	return NULL;
}

/*
 *  Adds a vertex with a given content or info (in) to a graph (this).
 *  Returns true if successful, and false if a vertex with that content already exists.
 */
bool Graph::addVertex(const int &in, const double x, const double y) {
	if ( findVertex(in) != NULL)
		return false;
	vertexSet.insert(new Vertex(in, x, y));
	return true;
}


bool Graph::removeVertex(const int &in){
	auto found = vertexSet.find(new Vertex(in, 0, 0));
	if(found != vertexSet.end()){
		vertexSet.erase(found);
		return true;
	}
	return false;
}
/*
 * Adds an edge to a graph (this), given the contents of the source and
 * destination vertices and the edge weight (w).
 * Returns true if successful, and false if the source or destination vertex does not exist.
 */
bool Graph::addEdge(int id, const int &sourc, const int &dest) {
	auto v1 = findVertex(sourc);
	auto v2 = findVertex(dest);
	if (v1 == NULL || v2 == NULL)
		return false;
	double w = v1->distanceTo(v2);
	v1->addEdge(id, v2,w);
	return true;
}


/**************** Single Source Shortest Path algorithms ************/
/*
void Graph::dijkstraShortestPath(const int &origin) {
	auto s = initSingleSource(origin);
	MutablePriorityQueue<Vertex> q;
	q.insert(s);
	while ( ! q.empty() ) {
		auto v = q.extractMin();
		for (auto e : v->adj) {
			auto oldDist = e.dest->dist;
			if (relax(v, e.dest, e.weight)) {
				if (oldDist == INF)
				q.insert(e.dest);
				else
				q.decreaseKey(e.dest);
			}
		}
	}
}
*/
/**************** Extracting graph info ************/

void Graph::getGraphInfo(){
	std::ifstream inFile;

	inFile.open("T03_nodes_X_Y_Fafe.txt");

	if (!inFile) {
		cerr << "Unable to open file datafile.txt";
		exit(1);   // call system to stop
	}

	std::string line;

	int idNo = 0;
	double X = 0;
	double Y = 0;


	std::getline(inFile, line);
	while (std::getline(inFile, line)) {
		std::stringstream linestream(line);
		std::string data;
		char dummy_char;

		linestream >> dummy_char;


		linestream >> idNo;

		std::getline(linestream, data, ',');
		linestream >> X;

		std::getline(linestream, data, ',');
		linestream >> Y;
		//std::cout << idNo << "\t" << X << "\t" << Y << endl;
		this->addVertex(idNo, X, Y);
	}

	inFile.close();

	inFile.open("T03_edges_Fafe.txt");

	if (!inFile) {
		cerr << "Unable to open file datafile.txt";
		exit(1);   // call system to stop
	}

	int idAresta = 0;
	int idNoOrigem = 0;
	int idNoDestino = 0;

	std::getline(inFile, line);
	while (std::getline(inFile, line)) {
		std::stringstream linestream(line);
		std::string data;

		char dummy_char;

		linestream >> dummy_char;

		linestream >> idNoOrigem;
		std::getline(linestream, data, ','); 
		linestream >> idNoDestino;
		//std::cout << idAresta << "\t" << idNoOrigem << "\t" << idNoDestino << endl;
		this->addEdge(idAresta, idNoOrigem, idNoDestino);
		idAresta++;

	}

	inFile.close();
}

Graph Graph::getTranspose() {
    Graph g = *this;

    Vertex *orig;
    Vertex *dest;
    int id;
    double weight;

    int iterator;

    for (Vertex *v : g.vertexSet) {
        dest = v;
        iterator = 0;
        for (Edge e : v->adj) {
            orig = e.dest;
            id = e.id;
            weight = e.weight;

            v->adj.erase(v->adj.begin() + iterator);
            orig->addEdge(id, dest, weight);
            iterator++;
        }
    }

    return g;
}

void Graph::eraseNotConnected(const int &start){
    this->unvisit();

    /*Depth-First Search using G and push to stack*/

    Graph gr = getTranspose();

    this->unvisit();
    /*pop from stack and Depth-First Search using Gr from poped vertex*/
}

void Graph::unvisit(){
    for(Vertex* v : this->vertexSet){
        v->visited = false;
    }
}



/******************EDGE*********************/
Edge::Edge(int id, Vertex *d, double w) : id(id), dest(d), weight(w) {}

/******************VERTEX*********************/
Vertex::Vertex(int in, const double x, const double y) : info(in), X(x), Y(y) {}

/*
 * Auxiliary function to add an outgoing edge to a vertex (this),
 * with a given destination vertex (d) and edge weight (w).
 */

void Vertex::addEdge(int id, Vertex *d, double w) {
    adj.push_back(Edge(id, d, w));
}

bool Vertex::operator<(Vertex &vertex) const {
    return this->dist < vertex.dist;
}

int Vertex::getInfo() const { return this->info; }

double Vertex::getDist() const { return this->dist; }

Vertex *Vertex::getPath() const { return this->path; }

double Vertex::getX() const { return this->X; }

double Vertex::getY() const { return this->Y; }

double Vertex::distanceTo(const Vertex *v) {
    return sqrt((v->getX() * v->getX()) + (v->getY() * v->getY()));
}