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

Array<Array<int> *> *test()
{
    Array<int> *test1 = new Array<int>();
    Array<int> &test11 = *test1;

    test11.addBack(1);
    test11.addBack(2);
    test11.addBack(3);
    Array<int> *test2 = new Array<int>();
    test2->addBack(4);
    test2->addBack(5);
    test2->addBack(6);

    Array<Array<int> *> *test3 = new Array<Array<int> *>();
    test3->addBack(test1);
    test3->addBack(test2);

    std::cout << (*test3)[0]->toString();
    std::cout << (*test3)[1]->toString();

    return test3;
}

int **test2()
{
    int *test = new int[2];
    test[0] = 1;
    test[1] = 2;
    int *test23 = new int[2];
    test23[0] = 3;
    test23[1] = 4;
    int **test3 = new int *[2];
    test3[0] = test;
    test3[1] = test23;
    return test3;
}

int main()
{
    // std::cout << "test2" << std::endl;
    // int **test4 = test2();
    // std::cout << test4[0][0] << std::endl;
    // std::cout << test4[0][1] << std::endl;
    // std::cout << test4[1][0] << std::endl;
    // std::cout << test4[1][1] << std::endl;

    // Array<Array<int> *> *test3 = test();
    // std::cout << test3[0][0]->toString();
    // std::cout << test3[0][1]->toString();

    Graph *graph = new Graph(0, 0);
    Menu menu("Main Menu", mainMenuItems, graph);
    menu.run();
    return 0;
}
