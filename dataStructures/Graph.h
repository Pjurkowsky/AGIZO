#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>

#include "AdjacencyList.h"
#include "IncidenceMatrix.h"
#include "../utils/RandomGenerator.h"

class Graph
{
public:
    Graph(int numOfVertices, int numOfEdges);                                                       // constructor
    Graph(int numOfVertices, float density, int minWeight, int maxWeight, bool directed = true);    // constructor
    ~Graph();                                                                                       // destructor
    void addEdge(int from, int to, int weight = 1);                                                 // method for adding edge to the graph
    AdjacencyList &getAdjList();                                                                    // method for getting the adjacency list
    IncidenceMatrix &getIncMatrix();                                                                // method for getting the incidence matrix
    Graph *generateDriectedGraph(int numOfVertices, float density, int minWeight, int maxWeight);   // method for generating directed graph
    Graph *generateUndriectedGraph(int numOfVertices, float density, int minWeight, int maxWeight); // method for generating undirected graph
    int getNumOfVertices();                                                                         // method for getting the number of vertices
    int getNumOfEdges();                                                                            // method for getting the number of edges

private:
    AdjacencyList adjList;
    IncidenceMatrix incMatrix;
    int _numOfVertices, _numOfEdges;
};

#endif