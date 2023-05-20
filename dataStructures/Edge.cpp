#include "Edge.h"

Edge::Edge(int from, int to, int weight) : _from(from), _to(to), _weight(weight) {}
Edge::Edge() : _from(-1), _to(-1), _weight(-1) {}

Edge::~Edge() {}

int Edge::getFrom()
{
    return _from;
}

int Edge::getTo()
{
    return _to;
}

int Edge::getWeight()
{
    return _weight;
}

std::ostream &operator<<(std::ostream &os, Edge &edge)
{
    os << edge._from << " -> " << edge._to << " (" << edge._weight << ")";
    return os;
}

bool operator==(const Edge &lhs, const Edge &rhs)
{
    return lhs._from == rhs._from && lhs._to == rhs._to && lhs._weight == rhs._weight;
}
