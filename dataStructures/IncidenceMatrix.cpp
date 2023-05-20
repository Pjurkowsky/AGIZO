#include "IncidenceMatrix.h"

IncidenceMatrix::IncidenceMatrix(int numOfVertices, int numOfEdges) : matrix(), numOfVertices(numOfVertices), numOfEdges(numOfEdges), edgeCounter(0)
{
    for (int i = 0; i < numOfVertices; i++)
    {
        matrix.addBack(new Array<int>());
        for (int j = 0; j < numOfEdges; j++)
            matrix[i]->addBack(0);
    }
}

IncidenceMatrix::~IncidenceMatrix()
{
}

void IncidenceMatrix::display()
{
    for (int i = 0; i < matrix.getLength(); i++)
    {
        for (int j = 0; j < matrix[i]->getLength(); j++)
            std::cout << std::setw(2) << (*matrix[i])[j] << " ";
        std::cout << std::endl;
    }
}

void IncidenceMatrix::addEdge(int from, int to, int weight)
{
    if (from >= numOfVertices)
        return;
    if (to >= numOfVertices)
        return;
    (*matrix[from])[edgeCounter] = weight;
    (*matrix[to])[edgeCounter] = -weight;
    edgeCounter++;
}

Array<int> IncidenceMatrix::findAdjacent(int vertex)
{
    Array<int> adjacent;
    for (int i = 0; i < matrix[vertex]->getLength(); i++)
    {
        if ((*matrix[vertex])[i] != 0 && (*matrix[vertex])[i] > 0)
        {
            for (int j = 0; j < matrix.getLength(); j++)
            {
                if ((*matrix[j])[i] != 0 && j != vertex)
                {
                    adjacent.addBack(j);
                    break;
                }
            }
        }
    }
    return adjacent;
}

Array<int> IncidenceMatrix::shorthestPathDijkstra(int start, int end)
{
    Array<int> distance;
    Array<int> previous;
    Array<int> unvisited;

    for (int i = 0; i < numOfVertices; i++)
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

        for (int i = 0; i < numOfEdges; i++)
        {
            if ((*matrix[minIndex])[i] != 0 && (*matrix[minIndex])[i] > 0)
            {
                for (int j = 0; j < numOfVertices; j++)
                {
                    if ((*matrix[j])[i] != 0 && j != minIndex)
                    {
                        if (distance[j] > distance[minIndex] + (*matrix[minIndex])[i]) // (*matrix[minIndex])[i] to jest chujowe, na pierwszej [] jest krawedz a na drugiej wierzcholek
                        {                                                              // czyli trzeba ogarnac jakos numer krawedzi bo minindex daje nam numer wierzcholka
                            distance[j] = distance[minIndex] + (*matrix[minIndex])[i];
                            previous[j] = minIndex;
                        }
                    }
                }
            }
        }

        // auto adjacent = findAdjacent(minIndex);
        // for (int i = 0; i < adjacent.getLength(); i++)
        // {
        //     std::cout << "Distance to " << adjacent[i] << ": " << (*matrix[minIndex])[i] << std::endl;
        //     if (distance[adjacent[i]] > distance[minIndex] + (*matrix[minIndex])[i]) // (*matrix[minIndex])[i] to jest chujowe, na pierwszej [] jest krawedz a na drugiej wierzcholek
        //     {                                                                        // czyli trzeba ogarnac jakos numer krawedzi bo minindex daje nam numer wierzcholka
        //         distance[adjacent[i]] = distance[minIndex] + (*matrix[minIndex])[i];
        //         previous[adjacent[i]] = minIndex;
        //     }
        // }
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

size_t IncidenceMatrix::getLength()
{
    return matrix.getLength();
}