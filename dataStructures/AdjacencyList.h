#ifndef ADJACENCY_LIST_H
#define ADJACENCY_LIST_H

#include <iostream>
#include "Array.h"
#include "LinkedList.h"
#include "Edge.h"

class AdjacencyList
{

public:
    AdjacencyList(int numOfVertices);
    ~AdjacencyList();
    void display();
    void addEdge(int from, int to, int weight = 1);

    Array<Array<int> *> *shorthestPathDijkstra(int start, int end);
    Array<Array<int> *> *shorthestPathBellmanFord(int start, int end);
    Array<Array<int> *> *minimalSpanningTreePrim(int start);
    Array<Array<int> *> *minimalSpanningTreeKruskal(int start);

    size_t getLength();

private:
    Array<LinkedList<Edge> *> adjList;
    int numOfVertices;
};

#endif