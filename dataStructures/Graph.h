#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>

#include "AdjacencyList.h"
#include "IncidenceMatrix.h"
#include "../utils/RandomGenerator.h"

class Graph
{
public:
    Graph(int numOfVertices, int numOfEdges);
    ~Graph();
    void addEdge(int from, int to, int weight = 1);
    AdjacencyList &getAdjList();
    IncidenceMatrix &getIncMatrix();
    Graph *generateRandom(int numOfVertices, float density, int minWeight, int maxWeight);

private:
    AdjacencyList adjList;
    IncidenceMatrix incMatrix;
    int _numOfVertices, _numOfEdges;
};

#endif