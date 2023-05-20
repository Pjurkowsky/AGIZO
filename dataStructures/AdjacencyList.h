#ifndef ADJACENCY_LIST_H
#define ADJACENCY_LIST_H

#include <iostream>
#include "Array.h"
#include "LinkedList.h"
#include "Edge.h"

class AdjacencyList
{

public:
    AdjacencyList(int numOFVertices);
    ~AdjacencyList();
    void display();
    void addEdge(int from, int to, int weight = 1);
    Array<int> shorthestPathDijkstra(int start, int end);
    size_t getLength();

private:
    Array<LinkedList<Edge> *> adjList;
    int numOfVertices;
};

#endif