#ifndef RANDOMGENERATOR_H
#define RANDOMGENERATOR_H

#include <iostream>
#include <chrono>
#include <random>
#include <fstream>
class RandomGenerator
{
public:
    RandomGenerator();                                    // constructor
    int generateRandomInteger();                          // generates random integer
    int *generateArrayOfIntegers(size_t size);            // generates array of random integers
    void generateFile(std::string filename, int numbers); // generates file with random integers

private:
    std::random_device rd;
    std::mt19937 rng;
    std::uniform_int_distribution<int> uint_dist;
};

#endif