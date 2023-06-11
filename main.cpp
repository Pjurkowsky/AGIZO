#include <iostream>
#include "dataStructures/Array.h"
#include "utils/Menu.h"
#include "dataStructures/AdjacencyList.h"
#include "dataStructures/IncidenceMatrix.h"

std::vector<MenuItem> displayOptions = {{"display matrix", {}},
                                        {"display list", {}},
                                        {"exit", {}}};

std::vector<MenuItem> menuItemsTree = {{"read from file", {}},
                                       {"generate graph", {}},
                                       {"display graph", {displayOptions}},
                                       {"prim's algorithm", {}},
                                       {"kruskal's algorithm", {}},
                                       {"exit", {}}};

std::vector<MenuItem> menuItemsPath = {{"read from file", {}},
                                       {"generate graph", {}},
                                       {"display graph", {displayOptions}},
                                       {"dijkstra algorithm", {}},
                                       {"bellman-ford algorithm", {}},
                                       {"exit", {}}};

std::vector<MenuItem> menuItemsFlow = {{"read from file", {}},
                                       {"generate graph", {}},
                                       {"display graph", {displayOptions}},
                                       {"ford-fulkerson algorithm", {}},
                                       {"exit", {}}};

std::vector<MenuItem> mainMenuItems = {{"minimal spanning tree problem", {menuItemsTree}},
                                       {"shorthest path problem", {menuItemsPath}},
                                       {"maximum flow problem", {menuItemsFlow}},
                                       {"exit", {}}};

std::vector<MenuItem> testMenuItems = {{"test shorthest path", {}},
                                       {"test mininal spanning tree", {}},
                                       {"exit", {}}};

int main(int argc, char const *argv[])
{
    Graph *graph = new Graph(0, 0);

    if (argc > 1)
    {
        for (int i = 0; i < argc; i++)
            if (strcmp(argv[i], "-t") == 0)
            {
                Menu menu("Test Menu", testMenuItems, graph);
                menu.run();
            }
    }
    else
    {
        Menu menu("Main Menu", mainMenuItems, graph);
        menu.run();
    }
    return 0;
}
