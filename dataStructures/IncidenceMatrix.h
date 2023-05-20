#ifndef INCIDENCE_MATRIX_H
#define INCIDENCE_MATRIX_H

#include <iostream>
#include <string>
#include <cstring>
#include <iomanip>

#include "Array.h"

class IncidenceMatrix
{

public:
    IncidenceMatrix(int numOfVertices, int numOfEdges);
    ~IncidenceMatrix();
    void display();
    void addEdge(int from, int to, int weight = 1);
    Array<int> shorthestPathDijkstra(int start, int end);
    size_t getLength();
    Array<int> findAdjacent(int vertex);

private:
    Array<Array<int> *> matrix;
    int numOfVertices, numOfEdges;
    int edgeCounter;
};

#endif