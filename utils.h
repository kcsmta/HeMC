#include <iostream>
#include <vector>
#include <random>
#include <stdexcept>


std::vector<double> generateRandomVector(int dimension, double lowerBound, double upperBound);

std::vector<double> generateConstantVector(int dimension, double value);

std::vector<double> Sign(std::vector<double> vec);

std::vector<double> generateRandomSign(int dimension);

void printVector(std::vector<double> vec);

