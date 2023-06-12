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

// method for finding shortest path using Dijkstra's algorithm
Array<Array<int> *> *AdjacencyList::shorthestPathDijkstra(int start, int end)
{
    Array<int> *dist = new Array<int>();
    Array<int> &distance = *dist;
    Array<int> previous;
    Array<int> unvisited;
    // setup distance, previous and unvisited arrays
    for (int i = 0; i < adjList.getLength(); i++)
    {
        distance.addBack(10000000);
        previous.addBack(-1);
        unvisited.addBack(i);
    }
    distance[start] = 0; // set distance of start vertex to 0

    while (unvisited.getLength() > 0) // for each unvisited vertex
    {
        int min = 10000000;
        int minIndex = -1;
        for (int i = 0; i < unvisited.getLength(); i++) // find the vertex with the smallest distance
        {
            if (distance[unvisited[i]] < min)
            {
                min = distance[unvisited[i]];
                minIndex = unvisited[i];
            }
        }
        // if (minIndex == end)
        // break;
        if (minIndex == -1) // if no vertex was found
            break;
        unvisited.remove(minIndex);

        auto current = adjList[minIndex]->getHead();
        while (current != nullptr) // for each neighbour of the vertex
        {
            Edge edge = current->data;
            if (distance[edge.getTo()] > distance[minIndex] + edge.getWeight()) // if the distance is smaller than the current distance
            {
                distance[edge.getTo()] = distance[minIndex] + edge.getWeight();
                previous[edge.getTo()] = minIndex;
            }
            current = current->next;
        }
    }

    Array<int> *path = new Array<int>();
    int current = end;
    if (previous[current] != -1) // if there is a path
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
    // setup distance and previous arrays
    for (int i = 0; i < adjList.getLength(); i++)
    {
        distance.addBack(10000000);
        previous.addBack(-1);
    }
    distance[start] = 0; // set distance of start vertex to 0

    for (int i = 0; i < adjList.getLength() - 1; i++) // for each vertex
    {
        for (int j = 0; j < adjList.getLength(); j++) // for each edge
        {
            auto current = adjList[j]->getHead(); // for each neighbour of the vertex
            while (current != nullptr)
            {
                Edge edge = current->data;
                if (distance[edge.getTo()] > distance[j] + edge.getWeight()) // if the distance is smaller than the current distance
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
    if (previous[current] != -1) // if there is a path
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
    // setup parent, key, mstSet and queue arrays
    for (int i = 0; i < adjList.getLength(); i++)
    {
        key.addBack(10000000);
        parent.addBack(-1);
        mstSet.addBack(false);
    }
    // set key of start vertex to 0 and add it to the queue
    key[start] = 0;
    queue.addBack(start);

    while (queue.getLength() > 0) // while there are vertices in the queue
    {
        int min = 10000000;
        int minIndex = -1;
        for (int i = 0; i < queue.getLength(); i++) // find the vertex with the smallest key
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
        while (current != nullptr) // for each neighbour of the vertex
        {
            Edge edge = current->data;
            if (mstSet[edge.getTo()] == false && edge.getWeight() < key[edge.getTo()]) // if the neighbour is not in the MST and the weight is smaller than the current key
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
        while (current != nullptr) // for each neighbour of the vertex
        {
            Edge edge = current->data;
            bool found = false;
            for (int j = 0; j < edges.getLength(); j++) // check if the edge is already in the array
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

    for (int i = 0; i < edges.getLength(); i++) // for each edge
    {
        int x = find(subset, edges[i].getFrom());
        int y = find(subset, edges[i].getTo());

        if (x != y) // if the vertices are not in the same subset
        {
            // add the edge to the result and merge the subsets
            result.addBack(edges[i]);
            Union(subset, x, y); //
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
}

size_t AdjacencyList::getLength()
{
    return adjList.getLength();
}

Array<LinkedList<Edge> *> &AdjacencyList::getAdjList()
{
    return adjList;
}
