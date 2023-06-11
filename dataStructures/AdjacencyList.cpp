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
    // add all one dir edges to a array
    Array<Edge> edges;
    for (int i = 0; i < adjList.getLength(); i++)
    {
        auto current = adjList[i]->getHead();
        while (current != nullptr)
        {
            Edge edge = current->data;
            bool found = false;
            for (int j = 0; j < edges.getLength(); j++)
            {
                if (edges[j].getFrom() == edge.getTo() && edges[j].getTo() == edge.getFrom())
                {
                    found = true;
                    break;
                }
            }
            if (!found)
                edges.addBack(edge);
            current = current->next;
        }
    }

    // sort edges by weight
    for (int i = 0; i < edges.getLength(); i++)
        for (int j = 0; j < edges.getLength() - 1; j++)
            if (edges[j].getWeight() > edges[j + 1].getWeight())
            {
                Edge temp = edges[j];
                edges[j] = edges[j + 1];
                edges[j + 1] = temp;
            }

    // create subsets
    Subset *subset = new Subset[numOfVertices];
    for (int i = 0; i < numOfVertices; i++)
    {
        subset[i].parent = i;
        subset[i].rank = 0;
    }

    Array<Edge> result;

    for (int i = 0; i < edges.getLength(); i++)
    {
        int x = find(subset, edges[i].getFrom());
        int y = find(subset, edges[i].getTo());

        if (x != y)
        {
            result.addBack(edges[i]);
            Union(subset, x, y);
        }
    }

    Array<Array<int> *> *resultArray = new Array<Array<int> *>();
    Array<int> *s = new Array<int>();
    Array<int> *e = new Array<int>();
    Array<int> *k = new Array<int>();

    for (int i = 0; i < result.getLength(); i++)
    {
        s->addBack(result[i].getFrom());
        e->addBack(result[i].getTo());
        k->addBack(result[i].getWeight());
    }

    resultArray->addBack(s);
    resultArray->addBack(e);
    resultArray->addBack(k);

    delete[] subset;

    return resultArray;
}

Array<Array<int> *> *AdjacencyList::maximumFlowFordFulkerson(int start, int end)
{
    // Array<Array<int> *> *result = new Array<Array<int> *>();
    // Array<int> flow;
    // Array<int> path;
    // Array<int> capacity;
    // Array<int> residualCapacity;
    // Array<int> parent;

    // for (int i = 0; i < adjList.getLength(); i++)
    // {
    //     flow.addBack(0);
    //     path.addBack(-1);
    //     capacity.addBack(0);
    //     residualCapacity.addBack(0);
    //     parent.addBack(-1);
    // }

    // int maxFlow = 0;

    // while (true)
    // {
    //     Array<Array<int> *> *pathArray = shorthestPathBFS(start, end);
    //     Array<int> *dist = (*pathArray)[0];
    //     Array<int> *path = (*pathArray)[1];

    //     if (path->getLength() == 0)
    //         break;

    //     int min = 10000000;
    //     for (int i = 0; i < path->getLength() - 1; i++)
    //     {
    //         int from = (*path)[i];
    //         int to = (*path)[i + 1];
    //         int index = -1;
    //         auto current = adjList[from]->getHead();
    //         while (current != nullptr)
    //         {
    //             index++;
    //             if (current->data.getTo() == to)
    //                 break;
    //             current = current->next;
    //         }
    //         if (index == -1)
    //             continue;
    //         if (min > (*dist)[to] - (*dist)[from])
    //             min = (*dist)[to] - (*dist)[from];
    //     }

    //     for (int i = 0; i < path->getLength() - 1; i++)
    //     {
    //         int from = (*path)[i];
    //         int to = (*path)[i + 1];
    //         int index = -1;
    //         auto current = adjList[from]->getHead();
    //         while (current != nullptr)
    //         {
    //             index++;
    //             if (current->data.getTo() == to)
    //                 break;
    //             current = current->next;
    //         }
    //         if (index == -1)
    //             continue;
    //         if (current->data.getWeight() - flow[from] > 0)
    //         {
    //             flow[from] += min;
    //             capacity[index] += min;
    //             residualCapacity[index] = current->data.getWeight() - flow[from];
    //         }
    //         else
    //         {
    //             flow[from] -= min;
    //             capacity[index] -= min;
    //             residualCapacity[index] = current->data.getWeight() - flow[from];
    //         }
    //     }

    //     maxFlow += min;
    // }

    // result->addBack(&flow);
    // result->addBack(&capacity);
    // result->addBack(&residualCapacity);

    // return result;
}

size_t AdjacencyList::getLength()
{
    return adjList.getLength();
}

Array<LinkedList<Edge> *> &AdjacencyList::getAdjList()
{
    return adjList;
}
