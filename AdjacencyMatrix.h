#pragma once

#include <cstdio>

class AdjacencyMatrix {
    //Class variables
    size_t citiesNumber;
    int **matrix = nullptr;

    void allocate(); //initializes matrix table with zeroes
    void deallocate(); //deletes matrix table

    void initialize(const int *distances); //fills matrix with values from 1d table
    void initialize(int **distances); //fills matrix with values from 2d table
    void copy(int **existingMatrix);

public:
    AdjacencyMatrix();
    AdjacencyMatrix(const size_t &verticesNumber, const int *edges);
    AdjacencyMatrix(const size_t &verticesNumber, int **distances);
    AdjacencyMatrix(const AdjacencyMatrix &existingMatrix);

    ~AdjacencyMatrix();

    void print(); //prints matrix to std::cout

    int **getMatrix() const {
        return this->matrix;
    }

    int getCost(const size_t &origin, const size_t &destination) const {
        return this->matrix[origin][destination];
    }

    int getCitiesNumber() const {
        return this->citiesNumber;
    }
};
