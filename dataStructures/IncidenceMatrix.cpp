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

// method for displaying the graph
void IncidenceMatrix::display()
{
    for (int i = 0; i < matrix.getLength(); i++)
    {
        for (int j = 0; j < matrix[i]->getLength(); j++)
            std::cout << std::setw(2) << (*matrix[i])[j] << " ";
        std::cout << std::endl;
    }
}
// method for adding edge to the graph
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
// method for adding undirected edge to the graph
void IncidenceMatrix::addUndirectedEdge(int from, int to, int weight)
{
    if (from >= numOfVertices)
        return;
    if (to >= numOfVertices)
        return;
    (*matrix[from])[edgeCounter] = weight;
    (*matrix[to])[edgeCounter] = weight;

    edgeCounter++;
}
// method for finding shortest path using Dijkstra's algorithm
Array<Array<int> *> *IncidenceMatrix::shorthestPathDijkstra(int start, int end)
{
    Array<int> *dist = new Array<int>();
    Array<int> &distance = *dist;
    Array<int> previous;
    Array<int> unvisited;

    // setup distance, previous and unvisited arrays
    for (int i = 0; i < numOfVertices; i++)
    {
        distance.addBack(10000000);
        previous.addBack(-1);
        unvisited.addBack(i);
    }
    distance[start] = 0; // set distance of start vertex to 0

    // for each unvisited vertex
    while (unvisited.getLength() > 0)
    {
        int min = 10000000;
        int minIndex = -1;
        // find the vertex with the smallest distance
        for (int i = 0; i < unvisited.getLength(); i++)
        {
            if (distance[unvisited[i]] < min)
            {
                min = distance[unvisited[i]];
                minIndex = unvisited[i];
            }
        }
        // if (minIndex == end)
        //     break;
        if (minIndex == -1) // if no vertex was found
            break;

        unvisited.remove(minIndex); // remove the vertex from the unvisited list

        // for each edge of the vertex
        for (int i = 0; i < numOfEdges; i++)
        {
            // if the edge is not 0 and has positive value (meaning it is an edge from the vertex)
            if ((*matrix[minIndex])[i] != 0 && (*matrix[minIndex])[i] > 0)
            {
                for (int j = 0; j < numOfVertices; j++)
                {
                    if ((*matrix[j])[i] != 0 && j != minIndex)
                    { // relax the edge
                        if (distance[j] > distance[minIndex] + (*matrix[minIndex])[i])
                        {
                            distance[j] = distance[minIndex] + (*matrix[minIndex])[i];
                            previous[j] = minIndex;
                        }
                    }
                }
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
// method for finding shortest path using Bellman-Ford algorithm
Array<Array<int> *> *IncidenceMatrix::shorthestPathBellmanFord(int start, int end)
{
    Array<int> *dist = new Array<int>();
    Array<int> &distance = *dist;
    Array<int> previous;
    // setup distance and previous arrays
    for (int i = 0; i < numOfVertices; i++)
    {
        distance.addBack(10000000);
        previous.addBack(-1);
    }
    distance[start] = 0; // set distance of start to 0

    // start Bellman-Ford algorithm
    for (int i = 0; i < numOfVertices - 1; i++)
    {
        // for each edge
        for (int j = 0; j < numOfEdges; j++)
        {
            for (int k = 0; k < numOfVertices; k++)
            {
                // if edge exists and has positive value (negative value means reverse edge)
                if ((*matrix[k])[j] != 0 && (*matrix[k])[j] > 0)
                { // find other vertex of this edge
                    for (int l = 0; l < numOfVertices; l++)
                    {
                        if ((*matrix[l])[j] != 0 && l != k)
                        {
                            // relax edge
                            if (distance[l] > distance[k] + (*matrix[k])[j])
                            {
                                distance[l] = distance[k] + (*matrix[k])[j];
                                previous[l] = k;
                            }
                        }
                    }
                }
            }
        }
    }

    Array<int> *path = new Array<int>();
    int current = end;
    if (previous[current] != -1) // if path exists
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

// method for finding minimal spanning tree using Prim's algorithm
Array<Array<int> *> *IncidenceMatrix::minimalSpanningTreePrim(int start)
{
    Array<int> *p = new Array<int>();
    Array<int> *k = new Array<int>();
    Array<int> &parent = *p;
    Array<int> &key = *k;

    Array<bool> mstSet;
    Array<int> queue;
    // setup parent, key, mstSet and queue arrays
    for (int i = 0; i < numOfVertices; i++)
    {
        key.addBack(10000000);
        parent.addBack(-1);
        mstSet.addBack(false);
    }
    // set key of start vertex to 0 and add it to the queue
    key[start] = 0;
    queue.addBack(start);

    while (queue.getLength() > 0) // while queue is not empty
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

        for (int i = 0; i < numOfEdges; i++) // for each edge of the vertex
        {
            if ((*matrix[minIndex])[i] != 0) // if edge exists
            {
                for (int j = 0; j < numOfVertices; j++) // find other vertex of the edge
                {
                    if ((*matrix[j])[i] != 0 && j != minIndex)
                    {
                        if (mstSet[j] == false && (*matrix[minIndex])[i] < key[j]) // if the vertex is not in the MST and the weight of the edge is smaller than the key of the vertex
                        {
                            parent[j] = minIndex;
                            key[j] = (*matrix[minIndex])[i];
                            queue.addBack(j);
                        }
                    }
                }
            }
        }
    }
    Array<Array<int> *> *result = new Array<Array<int> *>();
    result->addBack(k);
    result->addBack(p);
    return result;
}

Array<Array<int> *> *IncidenceMatrix::minimalSpanningTreeKruskal(int start)
{
    // add all one dir edges to a array
    Array<Edge> edges;
    for (int i = 0; i < numOfVertices; i++) // for each vertex
    {
        for (int j = 0; j < numOfEdges; j++) // for each edge
        {
            if ((*matrix[i])[j] != 0 && (*matrix[i])[j] > 0) // if edge exists
                for (int k = 0; k < numOfVertices; k++)
                {
                    if ((*matrix[k])[j] != 0 && k != i)
                    {
                        Edge edge(i, k, (*matrix[i])[j]);
                        bool found = false;
                        for (int l = 0; l < edges.getLength(); l++) // check if edge already exists
                        {
                            if (edges[l].getFrom() == edge.getTo() && edges[l].getTo() == edge.getFrom()) // if edge already exists
                            {
                                found = true;
                                break;
                            }
                        }
                        if (!found) // if edge does not exist
                            edges.addBack(edge);
                    }
                }
        }
    }

    // sort edges by weight
    for (int i = 0; i < edges.getLength(); i++)
    {
        for (int j = 0; j < edges.getLength() - 1; j++)
        {
            if (edges[j].getWeight() > edges[j + 1].getWeight())
            {
                Edge temp = edges[j];
                edges[j] = edges[j + 1];
                edges[j + 1] = temp;
            }
        }
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

        if (x != y) // if the edge does not create a cycle
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

// method for getting the number of vertices
size_t IncidenceMatrix::getLength()
{
    return matrix.getLength();
}