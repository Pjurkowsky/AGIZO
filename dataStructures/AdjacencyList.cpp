#include "AdjacencyList.h"

AdjacencyList::AdjacencyList(int numOfVertices) : adjList(), numOfVertices(numOfVertices)
{
    for (int i = 0; i < numOfVertices; i++)
        adjList.addBack(new LinkedList<Edge>());
}

AdjacencyList::~AdjacencyList()
{
}

void AdjacencyList::display()
{
    for (int i = 0; i < adjList.getLength(); i++)
        adjList[i]->display();
}

void AdjacencyList::addEdge(int from, int to, int weight)
{
    adjList[from]->addBack(Edge(from, to, weight));
}

Array<int> AdjacencyList::shorthestPathDijkstra(int start, int end)
{
    Array<int> distance;
    Array<int> previous;
    Array<int> unvisited;

    int u;
    for (int i = 0; i < adjList.getLength(); i++)
    {
        distance.addBack(10000000);
        previous.addBack(-1);
        unvisited.addBack(i);
    }
    distance[start] = 0;

    while (unvisited.getLength() > 0)
    {
        int min = 10000000;
        int minIndex = -1;
        for (int i = 0; i < unvisited.getLength(); i++)
        {
            if (distance[unvisited[i]] < min)
            {
                min = distance[unvisited[i]];
                minIndex = unvisited[i];
            }
        }
        if (minIndex == end)
            break;
        if (minIndex == -1)
            break;
        unvisited.remove(minIndex);

        auto current = adjList[minIndex]->getHead();
        while (current != nullptr)
        {
            Edge edge = current->data;
            if (distance[edge.getTo()] > distance[minIndex] + edge.getWeight())
            {
                distance[edge.getTo()] = distance[minIndex] + edge.getWeight();
                previous[edge.getTo()] = minIndex;
            }
            current = current->next;
        }
    }

    Array<int> path;
    int current = end;
    if (previous[current] != -1)
        while (current != start)
        {
            path.addFront(current);
            current = previous[current];
        }
    path.addFront(start);

    if (previous[end] == -1)
        std::cout << "No path found" << std::endl;
    else
    {
        std::cout << "Path: ";
        for (int i = 0; i < path.getLength(); i++)
        {
            std::cout << path[i];
            if (i < path.getLength() - 1)
                std::cout << " -> ";
        }
        std::cout << std::endl;
    }
    return distance;
}

size_t AdjacencyList::getLength()
{
    return adjList.getLength();
}
