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
    IncidenceMatrix(int numOfVertices, int numOfEdges);
    ~IncidenceMatrix();
    void display();
    void addEdge(int from, int to, int weight = 1);
    void addUndirectedEdge(int from, int to, int weight = 1);
    Array<Array<int> *> *shorthestPathDijkstra(int start, int end);
    Array<Array<int> *> *shorthestPathBellmanFord(int start, int end);
    Array<Array<int> *> *minimalSpanningTreePrim(int start);
    Array<Array<int> *> *minimalSpanningTreeKruskal(int start);
    size_t getLength();

private:
    Array<Array<int> *> matrix;
    int numOfVertices, numOfEdges;
    int edgeCounter;
};

#endif