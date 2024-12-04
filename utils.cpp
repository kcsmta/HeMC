#include "utils.h"


void printVector(std::vector<double> vec){
    for (size_t i = 0; i < vec.size(); ++i) {
        std::cout << vec[i] << " ";
    }
    std::cout << std::endl; // Add a newline after printing the vector
}

// Function to generate a random vector
std::vector<double> generateRandomVector(int dimension, double lowerBound, double upperBound) {
    // Validate inputs
    if (dimension <= 0) {
        throw std::invalid_argument("Dimension must be a positive integer.");
    }
    if (lowerBound >= upperBound) {
        throw std::invalid_argument("Lower bound must be less than upper bound.");
    }

    // Create a random number generator
    std::random_device rd;  // Seed generator
    std::mt19937 gen(rd()); // Mersenne Twister engine
    std::uniform_real_distribution<> dis(lowerBound, upperBound); // Uniform distribution [lowerBound, upperBound)

    // Generate the random vector
    std::vector<double> randomVector(dimension);
    for (int i = 0; i < dimension; ++i) {
        randomVector[i] = dis(gen);
    }

    return randomVector;
}