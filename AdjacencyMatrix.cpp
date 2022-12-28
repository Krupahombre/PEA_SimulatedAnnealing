//
// Created by KK on 11.12.2022.
//

#include "AdjacencyMatrix.h"

#include <iostream>

AdjacencyMatrix::AdjacencyMatrix(const AdjacencyMatrix &existingMatrix) {
    citiesNumber = existingMatrix.citiesNumber;

    //Initialize matrix table with zeroes
    allocate();

    copy(existingMatrix.getMatrix());
}

AdjacencyMatrix::AdjacencyMatrix(const size_t &verticesNumber, const int *edges) {
    if (edges == nullptr) {
        throw std::invalid_argument("Edges table cannot be null");
    }

    this->citiesNumber = verticesNumber;

    //Initialize matrix table with zeroes
    allocate();

    initialize(edges);
}

AdjacencyMatrix::AdjacencyMatrix(const size_t &verticesNumber, int **distances) {
    if (distances == nullptr) {
        throw std::invalid_argument("Edges table cannot be null");
    }

    this->citiesNumber = verticesNumber;

    //Initialize matrix table with zeroes
    allocate();

    initialize(distances);
}

AdjacencyMatrix::~AdjacencyMatrix() {
    this->deallocate();
}

void AdjacencyMatrix::allocate() {
    this->matrix = new int *[this->citiesNumber];

    for (int i = 0; i < this->citiesNumber; ++i) {
        this->matrix[i] = new int[this->citiesNumber]{};
    }
}

void AdjacencyMatrix::deallocate() {
    if (this->matrix == nullptr) {
        return;
    }

    for (int i = 0; i < this->citiesNumber; ++i) {
        delete[] this->matrix[i];
    }

    delete[] this->matrix;
    this->matrix = nullptr;
}

void AdjacencyMatrix::initialize(const int *edges) {
    int index = 0;

    for (int i = 0; i < this->citiesNumber; ++i) {

        for (int j = 0; j < this->citiesNumber; ++j) {
            this->matrix[i][j] = edges[index];
            index++;
        }
    }
}

void AdjacencyMatrix::initialize(int **distances) {
    int index = 0;

    for (int i = 0; i < this->citiesNumber; ++i) {

        for (int j = 0; j < this->citiesNumber; ++j) {
            this->matrix[i][j] = distances[i][j];
            index++;
        }
    }
}

void AdjacencyMatrix::copy(int **existingMatrix) {
    for (int i = 0; i < this->citiesNumber; ++i) {

        for (int j = 0; j < this->citiesNumber; ++j) {
            this->matrix[i][j] = existingMatrix[i][j];
        }
    }
}

void AdjacencyMatrix::print() {
    std::cout << "Adjacency matrix:\n";

    for (int i = 0; i < this->citiesNumber; ++i) {

        for (int j = 0; j < this->citiesNumber; ++j) {
            std::cout << "| " << matrix[i][j] << " ";
        }

        std::cout << "|\n";
    }
}

AdjacencyMatrix::AdjacencyMatrix() = default;