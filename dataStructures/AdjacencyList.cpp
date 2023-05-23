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

Array<Array<int> *> *AdjacencyList::shorthestPathDijkstra(int start, int end)
{
    Array<int> *dist = new Array<int>();
    Array<int> &distance = *dist;
    Array<int> previous;
    Array<int> unvisited;

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
        // if (minIndex == end)
        // break;
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

    Array<int> *path = new Array<int>();
    int current = end;
    if (previous[current] != -1)
        while (current != start)
        {
            path->addFront(current);
            current = previous[current];
        }
    path->addFront(start);

    if (previous[end] == -1)
        path->clear();

    Array<Array<int> *> *result = new Array<Array<int> *>();
    result->addBack(dist);
    result->addBack(path);

    return result;
}

Array<Array<int> *> *AdjacencyList::shorthestPathBellmanFord(int start, int end)
{
    Array<int> *dist = new Array<int>();
    Array<int> &distance = *dist;
    Array<int> previous;

    for (int i = 0; i < adjList.getLength(); i++)
    {
        distance.addBack(10000000);
        previous.addBack(-1);
    }
    distance[start] = 0;

    for (int i = 0; i < adjList.getLength() - 1; i++)
    {
        for (int j = 0; j < adjList.getLength(); j++)
        {
            auto current = adjList[j]->getHead();
            while (current != nullptr)
            {
                Edge edge = current->data;
                if (distance[edge.getTo()] > distance[j] + edge.getWeight())
                {
                    distance[edge.getTo()] = distance[j] + edge.getWeight();
                    previous[edge.getTo()] = j;
                }

                current = current->next;
            }
        }
    }

    Array<int> *path = new Array<int>();
    int current = end;
    if (previous[current] != -1)
        while (current != start)
        {
            path->addFront(current);
            current = previous[current];
        }
    path->addFront(start);

    if (previous[end] == -1)
        path->clear();

    Array<Array<int> *> *result = new Array<Array<int> *>();
    result->addBack(dist);
    result->addBack(path);
    return result;
}

Array<Array<int> *> *AdjacencyList::minimalSpanningTreePrim(int start)
{
    Array<int> *p = new Array<int>();
    Array<int> *k = new Array<int>();
    Array<int> &parent = *p;
    Array<int> &key = *k;

    Array<bool> mstSet;
    Array<int> queue;

    for (int i = 0; i < adjList.getLength(); i++)
    {
        key.addBack(10000000);
        parent.addBack(-1);
        mstSet.addBack(false);
    }

    key[start] = 0;
    queue.addBack(start);

    while (queue.getLength() > 0)
    {
        int min = 10000000;
        int minIndex = -1;
        for (int i = 0; i < queue.getLength(); i++)
        {
            if (key[queue[i]] < min)
            {
                min = key[queue[i]];
                minIndex = queue[i];
            }
        }
        queue.remove(minIndex);
        mstSet[minIndex] = true;

        auto current = adjList[minIndex]->getHead();
        while (current != nullptr)
        {
            Edge edge = current->data;
            if (mstSet[edge.getTo()] == false && edge.getWeight() < key[edge.getTo()])
            {
                parent[edge.getTo()] = minIndex;
                key[edge.getTo()] = edge.getWeight();
                queue.addBack(edge.getTo());
            }
            current = current->next;
        }
    }

    Array<Array<int> *> *result = new Array<Array<int> *>();
    result->addBack(k);
    result->addBack(p);
    return result;
}

Array<Array<int> *> *AdjacencyList::minimalSpanningTreeKruskal(int start)
{
    // sort Edges in ascending order
    Array<Edge> edges;
}

size_t AdjacencyList::getLength()
{
    return adjList.getLength();
}
