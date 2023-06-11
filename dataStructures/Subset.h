#ifndef SUBSET_H
#define SUBSET_H

#include <iostream>

struct Subset
{
    int parent;
    int rank;
};
int find(Subset subsets[], int i);
void Union(Subset subsets[], int x, int y);
#endif