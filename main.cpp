#include <iostream>
#include "utils/Menu.h"

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
                                       {"bellman–ford algorithm", {}},
                                       {"exit", {}}};

std::vector<MenuItem> menuItemsFlow = {{"read from file", {}},
                                       {"generate graph", {}},
                                       {"display graph", {displayOptions}},
                                       {"ford–fulkerson algorithm", {}},
                                       {"exit", {}}};

std::vector<MenuItem> mainMenuItems = {{"minimal spanning tree problem", {menuItemsTree}},
                                       {"shorthest path problem", {menuItemsPath}},
                                       {"maximum flow problem", {menuItemsFlow}},
                                       {"exit", {}}};

int main()
{

    Menu menu("Main Menu", mainMenuItems);
    menu.run();
    return 0;
}
