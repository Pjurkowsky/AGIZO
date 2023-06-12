#ifndef ADJACENCY_LIST_H
#define ADJACENCY_LIST_H

#include <iostream>
#include "Array.h"
#include "LinkedList.h"
#include "Edge.h"
#include "Subset.h"

class AdjacencyList
{

public:
    AdjacencyList(int numOfVertices);               // constructor
    ~AdjacencyList();                               // destructor
    void display();                                 // method for displaying the graph
    void addEdge(int from, int to, int weight = 1); // method for adding edge to the graph

    Array<Array<int> *> *shorthestPathDijkstra(int start, int end);    // method for finding shortest path using Dijkstra's algorithm
    Array<Array<int> *> *shorthestPathBellmanFord(int start, int end); // method for finding shortest path using Bellman-Ford algorithm
    Array<Array<int> *> *minimalSpanningTreePrim(int start);           // method for finding minimal spanning tree using Prim's algorithm
    Array<Array<int> *> *minimalSpanningTreeKruskal(int start);        // method for finding minimal spanning tree using Kruskal's algorithm
    Array<Array<int> *> *maximumFlowFordFulkerson(int start, int end);

    size_t getLength();                      // method for getting the number of vertices
    Array<LinkedList<Edge> *> &getAdjList(); // method for getting the adjacency list

private:
    Array<LinkedList<Edge> *> adjList;
    int numOfVertices;
};

#endif