#ifndef MENU_H
#define MENU_H

#include <iostream>
#include <string>
#include <fstream>
#include <random>
#include <ctime>
#include <climits>
#include <functional>
#include <algorithm>
#include <chrono>
#include <iomanip>

#include "MenuItem.h"
#include "Timer.h"
#include "RandomGenerator.h"
#include "../dataStructures/Graph.h"
#include "Tester.h"
class Menu
{
public:
    Menu(std::string name, std::vector<MenuItem> menuItems, Graph *graph); // constructor
    bool run();                                                            // runs menu

private:
    void waitForUser();                                                             // waits for user to press enter
    int getIntInput(std::string message);                                           // gets int input from
    float getFloatInput(std::string message);                                       // gets float input from user
    std::string getStringInput(std::string message);                                // gets string input from user
    void handleShortestPath(Array<Array<int> *> *result);                           // handles dijkstra and bellman-ford algorithms
    void handleMinimalSpanningTree(Array<Array<int> *> *result, int algorithmType); // handles prim and kruskal algorithms if algorithmType is 0 then it's prim, if 1 then it's kruskal
    void handleMaximumFlow(Array<Array<int> *> *result);                            // handles ford-fulkerson algorithm
    std::vector<MenuItem> menuItems;
    bool innerLoop;
    std::string menuName;
    Graph *graph;
};

#endif
