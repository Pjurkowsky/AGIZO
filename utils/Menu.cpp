#include "Menu.h"
#ifdef _WIN32
#define CLEAR "cls"
#else
#define CLEAR "clear"
#endif

Menu::Menu(std::string name, std::vector<MenuItem> menuItems, Graph *graph) : menuName(name), menuItems(menuItems), innerLoop(false), graph(graph)
{
}

// runs menu
bool Menu::run()
{
    while (true)
    {
        system(CLEAR);
        int i = 1;
        std::cout << std::setw(menuName.length() * 1.6) << menuName << '\n';

        std::cout << std::string(menuName.length() * 2, '=') << '\n';
        for (auto &item : menuItems)
        {
            std::cout << i << ". " << item.str << '\n';
            i++;
        }

        int choice = getIntInput("Enter your choice: ");
        if (choice > 0 && choice <= menuItems.size())
        {
            MenuItem chosenItem = menuItems[choice - 1];
            if (chosenItem.menuItems.size() > 0)
            {
                innerLoop = true;
                while (innerLoop)
                {
                    Menu menu(chosenItem.str, chosenItem.menuItems, graph);
                    innerLoop = menu.run();
                }
            }
            else
            {
                std::string chosenItemString = chosenItem.str;
                if (chosenItemString == "exit")
                    return false;
                else if (chosenItemString == "read from file")
                {
                    std::ifstream file(getStringInput("Enter filename: "));
                    if (!file)
                    {
                        std::cout << "Unable to open file" << '\n';
                        waitForUser();
                    }
                    else
                    {
                        delete graph;
                        int numberOfVertices, numberOfEdges, from, to, weight;
                        file >> numberOfEdges >> numberOfVertices;

                        graph = new Graph(numberOfVertices, numberOfEdges);

                        while (file >> from >> to >> weight)
                        {
                            if (menuName == "minimal spanning tree problem")
                            {
                                graph->getAdjList().addEdge(from, to, weight);
                                graph->getAdjList().addEdge(to, from, weight);
                                graph->getIncMatrix().addUndirectedEdge(to, from, weight);
                            }
                            else
                                graph->addEdge(from, to, weight);
                        }

                        file.close();
                        std::cout << "File read successfully - Graph loaded" << '\n';
                        waitForUser();
                    }
                }
                else if (chosenItemString == "generate graph")
                {
                    int numberOfVertices = getIntInput("Enter number of vertices: ");
                    while (numberOfVertices < 0)
                    {
                        std::cout << "Number of vertices must be greater than 0" << '\n';
                        numberOfVertices = getIntInput("Enter number of vertices: ");
                    }

                    float density = getFloatInput("Enter density of graph: ");
                    while (density < 0 || density > 1)
                    {
                        std::cout << "Density must be between 0 and 1" << '\n';
                        density = getFloatInput("Enter density of graph: ");
                    }

                    int minWeight = getIntInput("Enter minimum weight: ");
                    while (minWeight < 1)
                    {
                        std::cout << "Minimum weight must be greater or equal than 1" << '\n';
                        minWeight = getIntInput("Enter minimum weight: ");
                    }

                    int maxWeight = getIntInput("Enter maximum weight: ");
                    while (maxWeight < minWeight)
                    {
                        std::cout << "Maximum weight must be greater than minimum weight" << '\n';
                        maxWeight = getIntInput("Enter maximum weight: ");
                    }

                    Graph *newGraph;

                    if (menuName == "minimal spanning tree problem")
                        newGraph = graph->generateUndriectedGraph(numberOfVertices, density, minWeight, maxWeight);
                    else
                        newGraph = graph->generateDriectedGraph(numberOfVertices, density, minWeight, maxWeight);

                    delete graph;
                    graph = newGraph;

                    waitForUser();
                }
                else if (chosenItemString == "kruskal's algorithm")
                {
                    if (graph == nullptr || graph->getAdjList().getLength() == 0)
                    {
                        std::cout << "Graph is empty \n";
                        waitForUser();
                        continue;
                    }
                    std::cout << "List of available vertices: \n";
                    for (int i = 0; i < graph->getAdjList().getLength(); i++)
                        std::cout << i << ' ';
                    std::cout << '\n';
                    int start = getIntInput("Enter starting vertex: ");
                    std::cout << "Adjacency list: \n";
                    handleMinimalSpanningTree(graph->getAdjList().minimalSpanningTreeKruskal(start), 1);
                    std::cout << "Incidence matrix: \n";
                    handleMinimalSpanningTree(graph->getIncMatrix().minimalSpanningTreeKruskal(start), 1);
                    waitForUser();
                }
                else if (chosenItemString == "prim's algorithm")
                {
                    if (graph == nullptr || graph->getAdjList().getLength() == 0)
                    {
                        std::cout << "Graph is empty \n";
                        waitForUser();
                        continue;
                    }
                    std::cout << "List of available vertices: \n";
                    for (int i = 0; i < graph->getAdjList().getLength(); i++)
                        std::cout << i << ' ';
                    std::cout << '\n';
                    int start = getIntInput("Enter starting vertex: ");
                    std::cout << "Adjacency list: \n";
                    handleMinimalSpanningTree(graph->getAdjList().minimalSpanningTreePrim(start), 0);
                    std::cout << "Incidence matrix: \n";
                    handleMinimalSpanningTree(graph->getIncMatrix().minimalSpanningTreePrim(start), 0);
                    waitForUser();
                }
                else if (chosenItemString == "bellman-ford algorithm")
                {
                    if (graph == nullptr || graph->getIncMatrix().getLength() == 0)
                    {
                        std::cout << "Graph is empty \n";
                        waitForUser();
                        continue;
                    }
                    std::cout << "List of available vertices: \n";
                    for (int i = 0; i < graph->getAdjList().getLength(); i++)
                        std::cout << i << ' ';
                    std::cout << '\n';
                    int start = getIntInput("Enter starting vertex: ");
                    int end = getIntInput("Enter end vertex: ");
                    std::cout << "Adjacency list: \n";
                    handleShortestPath(graph->getAdjList().shorthestPathBellmanFord(start, end));
                    std::cout << "Incidence matrix: \n";
                    handleShortestPath(graph->getIncMatrix().shorthestPathBellmanFord(start, end));
                    waitForUser();
                }
                else if (chosenItemString == "dijkstra algorithm")
                {
                    if (graph == nullptr || graph->getIncMatrix().getLength() == 0)
                    {
                        std::cout << "Graph is empty \n";
                        waitForUser();
                        continue;
                    }

                    std::cout << "List of available vertices: \n";
                    for (int i = 0; i < graph->getAdjList().getLength(); i++)
                        std::cout << i << ' ';
                    std::cout << '\n';

                    int start = getIntInput("Enter starting vertex: ");
                    int end = getIntInput("Enter end vertex: ");

                    std::cout << "Adjacency list: \n";
                    handleShortestPath(graph->getAdjList().shorthestPathDijkstra(start, end));

                    std::cout << "Incidence matrix: \n";
                    handleShortestPath(graph->getIncMatrix().shorthestPathDijkstra(start, end));

                    waitForUser();
                }
                else if (chosenItemString == "ford-fulkerson algorithm")
                {
                    if (graph == nullptr || graph->getIncMatrix().getLength() == 0)
                    {
                        std::cout << "Graph is empty \n";
                        waitForUser();
                        continue;
                    }
                    std::cout << "List of available vertices: \n";
                    for (int i = 0; i < graph->getAdjList().getLength(); i++)
                        std::cout << i << ' ';
                    std::cout << '\n';
                    int start = getIntInput("Enter starting vertex: ");
                    int end = getIntInput("Enter end vertex: ");
                    std::cout << "Adjacency list: \n";

                    waitForUser();
                }
                else if (chosenItemString == "display matrix")
                {
                    graph->getIncMatrix().display();
                    waitForUser();
                }
                else if (chosenItemString == "display list")
                {
                    graph->getAdjList().display();
                    waitForUser();
                }
                else if (chosenItemString == "test shorthest path")
                {

                    Tester tester = Tester(2);
                    tester.testAlgorithm("test shorthest path");

                    waitForUser();
                }
                else if (chosenItemString == "test mininal spanning tree")
                {

                    Tester tester = Tester(100);
                    tester.testAlgorithm("test mininal spanning tree");

                    waitForUser();
                }
                else
                {
                    std::cout << "Not implemented yet" << std::endl;
                    waitForUser();
                }
            }
        }
        else
        {
            std::cout << "Invalid choice" << std::endl;
            waitForUser();
        }
    }
}

// waits for user to press enter
void Menu::waitForUser()
{
    std::cin.clear();
    std::cin.ignore(INT_MAX, '\n');
    std::cout << "Press any key to continue . . .\n";
    std::cin.get();
}
// gets int input from user
int Menu::getIntInput(std::string message)
{
    int x;
    std::cout << message;
    std::cin >> x;
    return x;
}
// gets float input from user
float Menu::getFloatInput(std::string message)
{
    float x;
    std::cout << message;
    std::cin >> x;
    return x;
}
// gets string input from user
std::string Menu::getStringInput(std::string message)
{
    std::string x;
    std::cout << message;
    std::cin >> x;
    return x;
}
// handles shortest path result
void Menu::handleShortestPath(Array<Array<int> *> *result)
{
    Array<int> &distances = *(*result)[0];
    Array<int> &path = *(*result)[1];

    if (path.getLength() == 0)
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

    std::cout << "Shortest distances: \n";
    for (int i = 0; i < distances.getLength(); i++)
        if (distances[i] == 10000000)
            std::cout << i << ": INF \n";
        else
            std::cout << i << ": " << distances[i] << '\n';
    std::cout << '\n';
    delete result;
}

// handles minimal spanning tree result if algorithmType is 0 then it's prim's algorithm, if it's 1 then it's kruskal's algorithm
void Menu::handleMinimalSpanningTree(Array<Array<int> *> *result, int algorithmType)
{
    if (result->getLength() == 0)
    {
        std::cout << "No path found" << std::endl;
        return;
    }

    if (algorithmType == 0)
    {
        Array<int> &key = *(*result)[0];
        Array<int> &parent = *(*result)[1];

        int x = 0;

        for (int i = 0; i < graph->getAdjList().getLength(); i++)
            if (parent[i] != -1)
            {
                std::cout << parent[i] << " <-> " << i << " (" << key[i] << ')' << std::endl;
                x++;
            }
        int sum = 0;
        for (int i = 0; i < x + 1; i++)
            sum += key[i];
        std::cout << "Sum: " << sum << std::endl;
        delete result;
    }
    else if (algorithmType == 1)
    {
        Array<int> &start = *(*result)[0];
        Array<int> &end = *(*result)[1];
        Array<int> &weight = *(*result)[2];

        for (int i = 0; i < weight.getLength(); i++)
            std::cout << start[i] << " <-> " << end[i] << " (" << weight[i] << ')' << std::endl;

        int sum = 0;
        for (int i = 0; i < weight.getLength(); i++)
            sum += weight[i];
        std::cout << "Sum: " << sum << std::endl;
        delete result;
    }
    else
    {
        std::cout << "Invalid algorithm type" << std::endl;
        delete result;
    }
}

void Menu::handleMaximumFlow(Array<Array<int> *> *result)
{
    Array<int> &flow = *(*result)[0];
    Array<int> &path = *(*result)[1];
    Array<int> &capacity = *(*result)[2];
    Array<int> &residualCapacity = *(*result)[3];
}
