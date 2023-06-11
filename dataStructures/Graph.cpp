#include "Graph.h"

Graph::Graph(int numOfVertices, int numOfEdges) : adjList(numOfVertices), incMatrix(numOfVertices, numOfEdges)
{
}

Graph::Graph(int numOfVertices, float density, int minWeight, int maxWeight, bool directed) : adjList(numOfVertices), incMatrix(numOfVertices, density * numOfVertices * (numOfVertices - 1) / 2)
{
    Graph *graph;
    if (directed)
        graph = generateDriectedGraph(numOfVertices, density, minWeight, maxWeight);
    else
        graph = generateUndriectedGraph(numOfVertices, density, minWeight, maxWeight);

    adjList = graph->getAdjList();
    incMatrix = graph->getIncMatrix();
    _numOfVertices = graph->getNumOfVertices();
    _numOfEdges = graph->getNumOfEdges();
}

Graph::~Graph()
{
}

void Graph::addEdge(int from, int to, int weight)
{
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

Graph *Graph::generateUndriectedGraph(int numOfVertices, float density, int minWeight, int maxWeight)
{

    RandomGenerator random;
    int maxNumOfEdges = numOfVertices * (numOfVertices - 1) / 2;
    int numOfEdges = maxNumOfEdges * density;

    Graph *graph = new Graph(numOfVertices, numOfEdges);

    int *nodesUnconnected = new int[numOfVertices];
    for (int i = 0; i < numOfVertices; i++)
    {
        nodesUnconnected[i] = i;
    }
    // shuffle nodesUNconnected
    for (int i = 0; i < numOfVertices; i++)
    {
        int index = random.generateRandomInt(0, numOfVertices - 1);
        int temp = nodesUnconnected[i];
        nodesUnconnected[i] = nodesUnconnected[index];
        nodesUnconnected[index] = temp;
    }

    Array<Edge> edges;
    for (int i = 0; i < numOfVertices; i++)
    {
        for (int j = i + 1; j < numOfVertices; j++)
        {
            edges.addBack(Edge(i, j, random.generateRandomInt(minWeight, maxWeight)));
        }
    }

    // add edges to graph to connect all nodes
    int numOfConnectedNodes = 0;
    int index = 0;
    while (numOfConnectedNodes < numOfVertices - 1)
    {
        int from = nodesUnconnected[index];
        int to = nodesUnconnected[index + 1];
        int weight = random.generateRandomInt(minWeight, maxWeight);
        graph->getAdjList().addEdge(from, to, weight);
        graph->getAdjList().addEdge(to, from, weight);
        graph->getIncMatrix().addUndirectedEdge(from, to, weight);
        numOfConnectedNodes++;
        index++;
    }

    // delete added edges from edges array
    for (int i = 0; i < graph->getAdjList().getLength(); i++)
    {
        auto current = graph->getAdjList().getAdjList()[i]->getHead();
        while (current != nullptr)
        {
            Edge edge = current->data;
            for (int j = 0; j < edges.getLength(); j++)
            {
                if (edges[j].getFrom() == edge.getFrom() && edges[j].getTo() == edge.getTo())
                {
                    edges.removeFromIndex(j);
                    break;
                }
            }
            current = current->next;
        }
    }

    for (int i = 0; i < numOfEdges - numOfConnectedNodes; i++)
    {
        int index = random.generateRandomInt(0, edges.getLength() - 1);
        graph->getAdjList().addEdge(edges[index].getFrom(), edges[index].getTo(), edges[index].getWeight());
        graph->getAdjList().addEdge(edges[index].getTo(), edges[index].getFrom(), edges[index].getWeight());
        graph->getIncMatrix().addUndirectedEdge(edges[index].getFrom(), edges[index].getTo(), edges[index].getWeight());
        edges.removeFromIndex(index);
    }

    return graph;
}

int Graph::getNumOfVertices()
{
    return _numOfVertices;
}

int Graph::getNumOfEdges()
{
    return _numOfEdges;
}

Graph *Graph::generateDriectedGraph(int numOfVertices, float density, int minWeight, int maxWeight)
{

    RandomGenerator random;
    int maxNumOfEdges = numOfVertices * (numOfVertices - 1);
    int numOfEdges = maxNumOfEdges * density;

    Graph *graph = new Graph(numOfVertices, numOfEdges);

    int *nodesUnconnected = new int[numOfVertices];
    for (int i = 0; i < numOfVertices; i++)
    {
        nodesUnconnected[i] = i;
    }

    // shuffle nodesUNconnected
    for (int i = 0; i < numOfVertices; i++)
    {
        int index = random.generateRandomInt(0, numOfVertices - 1);
        int temp = nodesUnconnected[i];
        nodesUnconnected[i] = nodesUnconnected[index];
        nodesUnconnected[index] = temp;
    }

    // generate all possible edges
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

    // add edges to graph to connect all nodes
    int numOfConnectedNodes = 0;
    int index = 0;
    while (numOfConnectedNodes < numOfVertices - 1)
    {
        int from = nodesUnconnected[index];
        int to = nodesUnconnected[index + 1];
        int weight = random.generateRandomInt(minWeight, maxWeight);
        graph->addEdge(from, to, weight);
        numOfConnectedNodes++;
        index++;
    }

    // delete added edges from edges array
    for (int i = 0; i < graph->getAdjList().getLength(); i++)
    {
        auto current = graph->getAdjList().getAdjList()[i]->getHead();
        while (current != nullptr)
        {
            Edge edge = current->data;
            for (int j = 0; j < edges.getLength(); j++)
            {
                if (edges[j].getFrom() == edge.getFrom() && edges[j].getTo() == edge.getTo())
                {
                    edges.removeFromIndex(j);
                    break;
                }
            }
            current = current->next;
        }
    }
    // add random edges to populate graph to desired density
    for (int i = 0; i < numOfEdges - numOfConnectedNodes; i++)
    {
        int index = random.generateRandomInt(0, edges.getLength() - 1);
        graph->addEdge(edges[index].getFrom(), edges[index].getTo(), edges[index].getWeight());
        edges.removeFromIndex(index);
    }

    return graph;
}
