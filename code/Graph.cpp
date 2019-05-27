#include "Graph.hpp"
using namespace std;

/******************GRAPH*********************/
int Graph::getNumVertex() const { return vertexSet.size(); }

unordered_set<Vertex *, HashById, VertexEqual> Graph::getVertexSet() const {
    return vertexSet;
}

/*
 * Auxiliary function to find a vertex with a given content.
 */
Vertex *Graph::findVertex(const int &in) const {
    auto found = vertexSet.find(new Vertex(in, 0, 0));
    if (found != vertexSet.end()) {
        return *found;
    }

    return NULL;
}

/*
 *  Adds a vertex with a given content or info (in) to a graph (this).
 *  Returns true if successful, and false if a vertex with that content already
 * exists.
 */
bool Graph::addVertex(const int &in, const double x, const double y) {
    if (findVertex(in) != NULL) return false;
    vertexSet.insert(new Vertex(in, x, y));
    return true;
}

bool Graph::removeVertex(const int &in) {
    auto found = vertexSet.find(new Vertex(in, 0, 0));
    if (found != vertexSet.end()) {
        vertexSet.erase(found);
        return true;
    }
    return false;
}
/*
 * Adds an edge to a graph (this), given the contents of the source and
 * destination vertices and the edge weight (w).
 * Returns true if successful, and false if the source or destination vertex
 * does not exist.
 */
bool Graph::addEdge(int id, const int &sourc, const int &dest) {
    auto v1 = findVertex(sourc);
    auto v2 = findVertex(dest);
    if (v1 == NULL || v2 == NULL) return false;
    double w = v1->distanceTo(v2);
    v1->addEdge(id, v2, w);
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

void Graph::getGraphInfo() {
    ifstream inFile;

    inFile.open("T03_nodes_X_Y_Fafe.txt");

    if (!inFile) {
        cerr << "Unable to open file datafile.txt";
        exit(1);  // call system to stop
    }

    string line;

    int idNo = 0;
    double X = 0;
    double Y = 0;

    getline(inFile, line);
    while (getline(inFile, line)) {
        stringstream linestream(line);
        string data;
        char dummy_char;

        linestream >> dummy_char;

        linestream >> idNo;

        getline(linestream, data, ',');
        linestream >> X;

        getline(linestream, data, ',');
        linestream >> Y;
        this->addVertex(idNo, X, Y);
    }

    inFile.close();

    inFile.open("T03_edges_Fafe.txt");

    if (!inFile) {
        cerr << "Unable to open file datafile.txt";
        exit(1);  // call system to stop
    }

    int idAresta = 0;
    int idNoOrigem = 0;
    int idNoDestino = 0;

    getline(inFile, line);
    while (getline(inFile, line)) {
        stringstream linestream(line);
        string data;

        char dummy_char;

        linestream >> dummy_char;

        linestream >> idNoOrigem;
        getline(linestream, data, ',');
        linestream >> idNoDestino;
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

void Graph::DFS(const int &s, stack<int> *stack) {
    Vertex *v = this->findVertex(s);
    v->visited = true;

    for (Edge e : v->adj) {
        if (e.dest->visited == false) this->DFS(e.dest->id, stack);
    }

    stack->push(s);
}

void Graph::visitComponents(const int &s) {
    Vertex *v = this->findVertex(s);
    v->visited = true;

    for (Edge e : v->adj) {
        if (e.dest->visited == false) {
            this->visitComponents(e.dest->id);
        }
    }
}

void Graph::eraseNotConnected(const int &start) {
    stack<int> stack;

    /* PUSH IN REVERSE ORDER */
    this->unvisit();
    this->DFS(start, &stack);

    Graph gr = getTranspose();

    /* POP FIRST TO GET CONNECTED GRAPH */
    this->unvisit();
    gr.visitComponents(start);

    for (vertex_set_t::iterator it_vertex = this->vertexSet.begin(); it_vertex != this->vertexSet.end();) {
        /* ALL UNVISITED VERTEXES */
        if (!(*it_vertex)->visited) {
            for (vertex_set_t::iterator it_vertex_orig = this->vertexSet.begin(); it_vertex_orig != this->vertexSet.end(); it_vertex_orig++) {
                /* ALL VISITED VERTEXES */
                if ((*it_vertex_orig)->visited) {
                    for (vector<Edge>::iterator it_edge = (*it_vertex_orig)->adj.begin(); it_edge != (*it_vertex_orig)->adj.end();) {
                        if ((*it_edge).dest == (*it_vertex)) {
                            /*REMOVE UNUSED EDGE*/
                            it_edge = (*it_vertex_orig)->adj.erase(it_edge);
                        }else{
                            ++it_edge;
                        }
                    }
                }
            }
            /* REMOVE VERTEX */
            it_vertex = this->vertexSet.erase(it_vertex);
        }else{
            ++it_vertex;
        }
    }
}

void Graph::unvisit() {
    for (Vertex *v : this->vertexSet) {
        v->visited = false;
    }
}

/******************EDGE*********************/
Edge::Edge(int id, Vertex *d, double w) : id(id), dest(d), weight(w) {}

/******************VERTEX*********************/
Vertex::Vertex(int in, const double x, const double y) : id(in), X(x), Y(y) {}

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

int Vertex::getId() const { return this->id; }

double Vertex::getDist() const { return this->dist; }

Vertex *Vertex::getPath() const { return this->path; }

double Vertex::getX() const { return this->X; }

double Vertex::getY() const { return this->Y; }

double Vertex::distanceTo(const Vertex *v) {
    return sqrt((v->getX() * v->getX()) + (v->getY() * v->getY()));
}