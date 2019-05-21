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
#include "MutablePriorityQueue.h"

using namespace std;

template <class T> class Edge;
template <class T> class Graph;
template <class T> class Vertex;

#define INF std::numeric_limits<double>::max()

/************************* Vertex  **************************/

template <class T>
class Vertex {
	T info;                // contents
	vector<Edge<T> > adj;  // outgoing edges
	bool visited;          // auxiliary field
	const double X, Y;
	double dist = 0;
	Vertex<T> *path = NULL;
	int queueIndex = 0; 		// required by MutablePriorityQueue

	bool processing = false;
	void addEdge(int id, Vertex<T> *dest, double w);

public:
	Vertex(T in, const double X, const double Y);
	bool operator<(Vertex<T> & vertex) const; // // required by MutablePriorityQueue
	T getInfo() const;
	double getDist() const;
	Vertex *getPath() const;
	double getX() const;
	double getY() const;
	double distanceTo(const Vertex* v);
	friend class Graph<T>;
	friend class MutablePriorityQueue<Vertex<T>>;
};


template <class T>
Vertex<T>::Vertex(T in, const double x, const double y): info(in),X(x),Y(y) {}

/*
 * Auxiliary function to add an outgoing edge to a vertex (this),
 * with a given destination vertex (d) and edge weight (w).
 */
template <class T>
void Vertex<T>::addEdge(int id, Vertex<T> *d, double w) {
	adj.push_back(Edge<T>(id, d, w));
}

template <class T>
bool Vertex<T>::operator<(Vertex<T> & vertex) const {
	return this->dist < vertex.dist;
}

template <class T>
T Vertex<T>::getInfo() const {
	return this->info;
}

template <class T>
double Vertex<T>::getDist() const {
	return this->dist;
}

template <class T>
Vertex<T> *Vertex<T>::getPath() const {
	return this->path;
}

template <class T>
double Vertex<T>::getX() const{
	return this->X;
}

template <class T>
double Vertex<T>::getY() const{
	return this->Y;
}

template <class T>
double Vertex<T>::distanceTo(const Vertex* v){
	return sqrt( (v->getX()*v->getX()) + (v->getY()*v->getY()));
}

/********************** Edge  ****************************/

template <class T>
class Edge {
	int id;
	Vertex<T> * dest;      // destination vertex
	double weight;         // edge weight
public:
	Edge(int id, Vertex<T> *d, double w);
	friend class Graph<T>;
	friend class Vertex<T>;
};

template <class T>
Edge<T>::Edge(int id, Vertex<T> *d, double w): id(id), dest(d), weight(w) {}



/*************************** Graph  **************************/

template <class T>
class Graph {
	vector<Vertex<T> *> vertexSet;    // vertex set

public:
	Vertex<T> *findVertex(const T &in) const;
	bool addVertex(const T &in, const double x, const double y);
	bool addEdge(int id, const T &sourc, const T &dest);
	int getNumVertex() const;
	vector<Vertex<T> *> getVertexSet() const;

	// Fp05 - single source
	void dijkstraShortestPath(const T &s);
	void dijkstraShortestPathOld(const T &s);
	void unweightedShortestPath(const T &s);
	void bellmanFordShortestPath(const T &s);
	void getGraphInfo();
	vector<T> getPath(const T &origin, const T &dest) const;

	// Fp05 - all pairs
	void floydWarshallShortestPath();
	vector<T> getfloydWarshallPath(const T &origin, const T &dest) const;

};

template <class T>
int Graph<T>::getNumVertex() const {
	return vertexSet.size();
}

template <class T>
vector<Vertex<T> *> Graph<T>::getVertexSet() const {
	return vertexSet;
}

/*
 * Auxiliary function to find a vertex with a given content.
 */
template <class T>
Vertex<T> * Graph<T>::findVertex(const T &in) const {
	for (auto v : vertexSet)
		if (v->info == in)
			return v;
	return NULL;
}

/*
 *  Adds a vertex with a given content or info (in) to a graph (this).
 *  Returns true if successful, and false if a vertex with that content already exists.
 */
template <class T>
bool Graph<T>::addVertex(const T &in, const double x, const double y) {
	if ( findVertex(in) != NULL)
		return false;
	vertexSet.push_back(new Vertex<T>(in, x, y));
	return true;
}

/*
 * Adds an edge to a graph (this), given the contents of the source and
 * destination vertices and the edge weight (w).
 * Returns true if successful, and false if the source or destination vertex does not exist.
 */
template <class T>
bool Graph<T>::addEdge(int id, const T &sourc, const T &dest) {
	auto v1 = findVertex(sourc);
	auto v2 = findVertex(dest);
	if (v1 == NULL || v2 == NULL)
		return false;
	double w = v1->distanceTo(v2);
	v1->addEdge(id, v2,w);
	return true;
}


/**************** Single Source Shortest Path algorithms ************/

template<class T>
void Graph<T>::dijkstraShortestPath(const T &origin) {
	auto s = initSingleSource(origin);
	MutablePriorityQueue<Vertex<T>> q;
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

/**************** Extracting graph info ************/

template<class T>
void Graph<T>::getGraphInfo(){
	ifstream inFile;

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
