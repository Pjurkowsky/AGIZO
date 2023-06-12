#ifndef INCIDENCE_MATRIX_H
#define INCIDENCE_MATRIX_H

#include <iostream>
#include <string>
#include <cstring>
#include <iomanip>

#include "Array.h"
#include "Edge.h"
#include "Subset.h"

class IncidenceMatrix
{

public:
    IncidenceMatrix(int numOfVertices, int numOfEdges);                // constructor
    ~IncidenceMatrix();                                                // destructor
    void display();                                                    // method for displaying the graph
    void addEdge(int from, int to, int weight = 1);                    // method for adding edge to the graph
    void addUndirectedEdge(int from, int to, int weight = 1);          // method for adding undirected edge to the graph
    Array<Array<int> *> *shorthestPathDijkstra(int start, int end);    // method for finding shortest path using Dijkstra's algorithm
    Array<Array<int> *> *shorthestPathBellmanFord(int start, int end); // method for finding shortest path using Bellman-Ford algorithm
    Array<Array<int> *> *minimalSpanningTreePrim(int start);           // method for finding minimal spanning tree using Prim's algorithm
    Array<Array<int> *> *minimalSpanningTreeKruskal(int start);        // method for finding minimal spanning tree using Kruskal's algorithm
    size_t getLength();

private:
    Array<Array<int> *> matrix;
    int numOfVertices, numOfEdges;
    int edgeCounter;
};

#endif