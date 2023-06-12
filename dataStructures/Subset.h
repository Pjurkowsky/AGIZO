#ifndef SUBSET_H
#define SUBSET_H

#include <iostream>

struct Subset
{
    int parent;
    int rank;
};
int find(Subset subsets[], int i);          // find the subset of an element i
void Union(Subset subsets[], int x, int y); // merge two subsets
#endif