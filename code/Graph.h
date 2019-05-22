/*
 * Graph.h
 */
#ifndef GRAPH_H_
#define GRAPH_H_

#include <vector>
#include <queue>
#include <list>
#include <limits>
#include <cmath>
#include <iostream>
#include <sstream>
#include <fstream>
#include <unordered_set>
#include "MutablePriorityQueue.h"

class Edge;
class Graph;
class Vertex;

#define INF std::numeric_limits<double>::max()


/********************** Edge  ****************************/

class Edge {
	int id;
	Vertex * dest;      // destination vertex
	double weight;         // edge weight
public:
	Edge(int id, Vertex *d, double w);
	friend class Graph;
	friend class Vertex;
};

Edge::Edge(int id, Vertex *d, double w): id(id), dest(d), weight(w) {}

/************************* Vertex  **************************/

class Vertex {
	int id;                // contents
	std::vector<Edge> adj;  // outgoing edges
	bool visited;          // auxiliary field
	const double X, Y;
	double dist = 0;
	Vertex *path = NULL;
	int queueIndex = 0; 		// required by MutablePriorityQueue

	bool processing = false;
	void addEdge(int id, Vertex *dest, double w);

public:
	Vertex(int id, const double X, const double Y);
	bool operator<(Vertex & vertex) const; // // required by MutablePriorityQueue
	int getId() const;
	double getDist() const;
	Vertex *getPath() const;
	double getX() const;
	double getY() const;
	double distanceTo(const Vertex* v);
	friend class Graph;
	friend class MutablePriorityQueue<Vertex>;
};

Vertex::Vertex(int id, const double x, const double y): id(id),X(x),Y(y) {}

/*
 * Auxiliary function to add an outgoing edge to a vertex (this),
 * with a given destination vertex (d) and edge weight (w).
 */
void Vertex::addEdge(int id, Vertex *d, double w) {
	adj.push_back(Edge(id, d, w));
}

bool Vertex::operator<(Vertex & vertex) const {
	return this->dist < vertex.dist;
}

int Vertex::getId() const {
	return this->id;
}

double Vertex::getDist() const {
	return this->dist;
}

Vertex *Vertex::getPath() const {
	return this->path;
}

double Vertex::getX() const{
	return this->X;
}

double Vertex::getY() const{
	return this->Y;
}

double Vertex::distanceTo(const Vertex* v){
	return sqrt( (v->getX()*v->getX()) + (v->getY()*v->getY()));
}

/*************************** Vertex Hash  **************************/

class VertexEqual {
public:
	bool operator()(const Vertex* v1, const Vertex* v2) const {
		return v1->getId() == v2->getId();
	}
};

class HashById {
public:
	size_t operator()(Vertex* const& v) const {
		int id = v->getId();
		return std::hash<int>()(id);
	}
};

/*************************** Graph  **************************/

class Graph {
	std::unordered_set<Vertex *, HashById, VertexEqual> vertexSet;    // vertex set

public:
	Vertex *findVertex(const int &in) const;
	bool addVertex(const int &in, const double x, const double y);
	bool removeVertex(const int &in);
	bool addEdge(int id, const int &sourc, const int &dest);
	int getNumVertex() const;
	std::unordered_set<Vertex *, HashById, VertexEqual> getVertexSet() const;

	// Fp05 - single source
	//void dijkstraShortestPath(const int &s);
	//void dijkstraShortestPathOld(const int &s);
	void unweightedShortestPath(const int &s);
	void bellmanFordShortestPath(const int &s);
	void getGraphInfo();
	std::vector<int> getPath(const int &origin, const int &dest) const;

	// Fp05 - all pairs
	void floydWarshallShortestPath();
	std::vector<int> getfloydWarshallPath(const int &origin, const int &dest) const;
};

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



#endif /* GRAPH_H_ */
