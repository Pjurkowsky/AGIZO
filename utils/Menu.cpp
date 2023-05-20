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
                        file >> numberOfVertices >> numberOfEdges;
                        graph = new Graph(numberOfVertices, numberOfEdges);

                        while (file >> from >> to >> weight)
                            graph->addEdge(from, to, weight);

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
                        std::cout << "Minimum weight must be greater than 0" << '\n';
                        minWeight = getIntInput("Enter minimum weight: ");
                    }

                    int maxWeight = getIntInput("Enter maximum weight: ");
                    while (maxWeight < minWeight)
                    {
                        std::cout << "Maximum weight must be greater than minimum weight" << '\n';
                        maxWeight = getIntInput("Enter maximum weight: ");
                    }

                    Graph *newGraph = graph->generateRandom(numberOfVertices, density, minWeight, maxWeight);

                    delete graph;
                    graph = newGraph;

                    waitForUser();
                }
                else if (chosenItemString == "kruskal's algorithm")
                {
                    std::cout << "Not implemented yet5" << std::endl;
                    waitForUser();
                }
                else if (chosenItemString == "prim's algorithm")
                {
                    std::cout << "Not implemented yet5" << std::endl;
                    waitForUser();
                }
                else if (chosenItemString == "bellman-ford algorithm")
                {
                    std::cout << "Not implemented yet5" << std::endl;
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
                    handleDijkstra(graph->getAdjList().shorthestPathDijkstra(start, end));

                    std::cout << "Incidence matrix: \n";
                    handleDijkstra(graph->getIncMatrix().shorthestPathDijkstra(start, end));

                    waitForUser();
                }
                else if (chosenItemString == "ford-fulkerson algorithm")
                {
                    std::cout << "Not implemented yet6 \n";
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

void Menu::handleDijkstra(Array<int> distances)
{
    std::cout << "Shortest distances: \n";
    for (int i = 0; i < distances.getLength(); i++)
        if (distances[i] == 10000000)
            std::cout << i << ": INF \n";
        else
            std::cout << i << ": " << distances[i] << '\n';
    std::cout << '\n';
}