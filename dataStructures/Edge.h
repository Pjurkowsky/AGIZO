#ifndef EDGE_H
#define EDGE_H

#include <iostream>

class Edge
{
public:
    Edge(int from, int to, int weight = 1);
    Edge();
    ~Edge();
    int getFrom();
    int getTo();
    int getWeight();
    friend std::ostream &operator<<(std::ostream &os, Edge &edge);
    friend bool operator==(const Edge &lhs, const Edge &rhs);

private:
    int _from;
    int _to;
    int _weight;
};

#endif
