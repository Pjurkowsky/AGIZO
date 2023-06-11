#include "Tester.h"

Tester::Tester(int numOfTests) : numOfTests(numOfTests)
{
}

void Tester::testAlgorithm(std::string type)
{
    double time[4][5][4] = {};
    int numOfVertices = 50;
    for (int z = 0; z < 5; z++)
    {
        numOfVertices = 50 * (z + 1);
        Timer timer;
        Graph *graph;
        for (int j = 0; j < 4; j++)
        {

            float density = 0.25 * (j + 1);
            int start = 0;
            int end = numOfVertices - 1;
            std::cout << "Number of verticies: " << numOfVertices << " "
                      << "Density: " << density << std::endl;
            graph = new Graph(numOfVertices, density, 1, 10);
            for (int i = 0; i < numOfTests; i++)
            {
                std::cout << "Test " << i + 1 << std::endl;
                if (type == "test shorthest path")
                {
                    timer.start();
                    graph->getAdjList().shorthestPathDijkstra(start, end);
                    timer.stop();
                    time[0][z][j] += timer.getElapsedTime();

                    timer.start();
                    graph->getAdjList().shorthestPathBellmanFord(start, end);
                    timer.stop();
                    time[1][z][j] += timer.getElapsedTime();

                    timer.start();
                    graph->getIncMatrix().shorthestPathDijkstra(start, end);
                    timer.stop();
                    time[2][z][j] += timer.getElapsedTime();

                    timer.start();
                    graph->getIncMatrix().shorthestPathBellmanFord(start, end);
                    timer.stop();
                    time[3][z][j] += timer.getElapsedTime();
                }
                else if (type == "test mininal spanning tree")
                {
                    timer.start();
                    graph->getAdjList().minimalSpanningTreePrim(start);
                    timer.stop();
                    time[0][z][j] += timer.getElapsedTime();

                    timer.start();
                    graph->getAdjList().minimalSpanningTreeKruskal(start);
                    timer.stop();
                    time[1][z][j] += timer.getElapsedTime();

                    timer.start();
                    graph->getIncMatrix().minimalSpanningTreeKruskal(start);
                    timer.stop();
                    time[2][z][j] += timer.getElapsedTime();

                    timer.start();
                    graph->getIncMatrix().minimalSpanningTreeKruskal(start);
                    timer.stop();
                    time[3][z][j] += timer.getElapsedTime();
                }
            }
            delete graph;
        }
    }

    std::ofstream file(type + ".txt");
    if (!file)
    {
        std::cout << "Error opening file" << std::endl;
        return;
    }
    file << "- "
         << "0.25 "
         << "0.5 "
         << "0.75 "
         << "1 " << '\n';

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            file << 50 * (j + 1);
            file << " " << time[i][j][0] / numOfTests;
            file << " " << time[i][j][1] / numOfTests;
            file << " " << time[i][j][2] / numOfTests;
            file << " " << time[i][j][3] / numOfTests;
            file << '\n';
        }
    }
    file.close();
}
