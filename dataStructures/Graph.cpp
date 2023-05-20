#include "Graph.h"

Graph::Graph(int numOfVertices, int numOfEdges) : adjList(numOfVertices), incMatrix(numOfVertices, numOfEdges)
{
}

Graph::~Graph()
{
}

void Graph::addEdge(int from, int to, int weight)
{
    std::cout << "Adding edge from " << from << " to " << to << " with weight " << weight << std::endl;
    adjList.addEdge(from, to, weight);
    incMatrix.addEdge(from, to, weight);
}

AdjacencyList &Graph::getAdjList()
{
    return adjList;
}

IncidenceMatrix &Graph::getIncMatrix()
{
    return incMatrix;
}

Graph *Graph::generateRandom(int numOfVertices, float density, int minWeight, int maxWeight)
{

    RandomGenerator random;
    int maxNumOfEdges = numOfVertices * (numOfVertices - 1);
    int numOfEdges = maxNumOfEdges * density;

    Graph *graph = new Graph(numOfVertices, numOfEdges);

    Array<Edge> edges;
    for (int i = 0; i < numOfVertices; i++)
    {
        for (int j = 0; j < numOfVertices; j++)
        {
            if (i == j)
                continue;
            edges.addBack(Edge(i, j, random.generateRandomInt(minWeight, maxWeight)));
        }
    }
    for (int i = 0; i < numOfEdges; i++)
    {
        int index = random.generateRandomInt(0, edges.getLength() - 1);
        graph->addEdge(edges[index].getFrom(), edges[index].getTo(), edges[index].getWeight());
        edges.removeFromIndex(index);
    }

    graph->incMatrix.display();
    return graph;
}
