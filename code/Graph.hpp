/*
 * Graph.h
 */
#ifndef GRAPH_H_
#define GRAPH_H_

#include <cmath>
#include <fstream>
#include <iostream>
#include <limits>
#include <list>
#include <queue>
#include <sstream>
#include <algorithm>
#include <stack>
#include <string>
#include <ctime>
#include <set>
#include <unordered_set>
#include "graphviewer.h"
#include "MutablePriorityQueue.h"

class Edge;
class Graph;
class Vertex;

#define INF std::numeric_limits<double>::max()

/********************** Edge  ****************************/

class Edge {
    int id;
    Vertex *dest;   // destination vertex
    double weight;  // edge weight
   public:
    Edge(int id, Vertex *d, double w);
    friend class Graph;
    friend class Vertex;
};

/************************* Vertex  **************************/

class Vertex {
    int id;                 // contents
    std::vector<Edge> adj;  // outgoing edges
    bool visited;           // auxiliary field
    const double X, Y;
    double dist = 0;
    Vertex *path = NULL;
    int queueIndex;

    bool processing = false;
    void addEdge(int id, Vertex *dest, double w);

   public:
    Vertex(int id, const double X, const double Y);
    bool operator<(Vertex &vertex) const;
    int getId() const;
    double getDist() const;
    Vertex *getPath() const;
    double getX() const;
    double getY() const;
    double getQueueIndex() const;
    void setQueueIndex(int queueIndex);
    double distanceTo(const Vertex *v);
    friend class Graph;
};

/*************************** Vertex Hash  **************************/

class VertexEqual {
   public:
    bool operator()(const Vertex *v1, const Vertex *v2) const {
        return v1->getId() == v2->getId();
    }
};

class HashById {
   public:
    size_t operator()(Vertex *const &v) const {
        int id = v->getId();
        return std::hash<int>()(id);
    }
};

/*************************** Graph  **************************/
typedef std::unordered_set<Vertex *, HashById, VertexEqual> vertex_set_t;
class Graph {
    vertex_set_t vertexSet;  // vertex set

   public:
    Graph() = default;
    //Graph(Graph g);
    Vertex *findVertex(const int &in) const;
    bool addVertex(const int &in, const double x, const double y);
    bool removeVertex(const int &in);
    bool addEdge(int id, const int &sourc, const int &dest);
    int getNumVertex() const;
    std::unordered_set<Vertex *, HashById, VertexEqual> getVertexSet() const;

    Vertex *initSingleSource(const int &origin);
    bool relax(Vertex *v, Vertex *w, double weight);
    void dijkstraShortestPath(const int &origin);
    void unweightedShortestPath(const int &s);
    void bellmanFordShortestPath(const int &s);
    void displayPath(GraphViewer *gv, std::vector<int> path);
    void displayGraph(GraphViewer *gv);
    void getGraphInfo(std::string nodes, std::string edges);
    std::vector<int> getPath(const int &dest) const;

    // Fp05 - all pairs
    void floydWarshallShortestPath();
    std::vector<int> getfloydWarshallPath(const int &origin, const int &dest) const;

    /* Strongly Connected Components*/
    //Graph getTranspose();
    unordered_set<int> getComponents(const int &start);
    void eraseNotConnected(unordered_set<int> max_set);
    void unvisit();
    void DFS(const int &s, std::stack<int> *stack);
    void visitComponents(const int &s, unordered_set<int> *comp);

    vector<int> getCircularPath(vector<int> &poi);
};

#endif /* GRAPH_H_ */
