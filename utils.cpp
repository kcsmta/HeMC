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
        double value;
        do {
            value = dis(gen);
        } while (value == 0.0); // Ensure the value is not 0
        randomVector[i] = value;
    }

    return randomVector;
}

std::vector<double> generateConstantVector(int dimension, double value) {
    // Validate inputs
    if (dimension <= 0) {
        throw std::invalid_argument("Dimension must be a positive integer.");
    }
    
    // Generate the constant vector
    std::vector<double> constantVector(dimension);
    for (int i = 0; i < dimension; ++i) {
        constantVector[i] = value;
    }

    return constantVector;
}

std::vector<double> generateRandomSign(int dimension) {
    // Validate inputs
    if (dimension <= 0) {
        throw std::invalid_argument("Dimension must be a positive integer.");
    }

    std::random_device rd;  // Seed generator
    std::mt19937 gen(rd()); // Mersenne Twister engine
    std::uniform_int_distribution<> dis(0, 1); // Uniform distribution {0, 1}

    // Generate the random sign vector
    std::vector<double> signVector(dimension);
    for (int i = 0; i < dimension; ++i) {
        signVector[i] = (dis(gen) == 0) ? -1 : 1; // Map 0 to -1, 1 to 1
    }

    return signVector;
}

std::vector<double> Sign(std::vector<double> vec){
    std::vector<double> signVec;
    for (size_t i = 0; i < vec.size(); ++i) {
        if(vec[i]<0){
            signVec.push_back(-1);
        }
        else{
            signVec.push_back(1);
        }
    } 
    return signVec;
}