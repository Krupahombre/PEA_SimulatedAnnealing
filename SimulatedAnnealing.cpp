#include <iostream>
#include "SimulatedAnnealing.h"

Path *SimulatedAnnealing::executeSA(AdjacencyMatrix &matrix, int epochLength, char swapMethod, char coolMethod, double coolingRate, int startTemperature) {
    int verticesNum = matrix.getCitiesNumber();
    std::vector<int> vertices;

    for (int i = 0; i < verticesNum; i++) {
        vertices.push_back(i);
    }

    fullShuffle(vertices);
    int cost = calculateCost(matrix, vertices);

    bestSolution = vertices;
    bestCost = cost;
    double currHeat = startTemperature;

    ////tests only
    //double currHeat = pow(matrix.getCitiesNumber(), 2) * 100.0;

    epoch = 0;

    while (currHeat > 1) {
        epoch++;

        for (int i = 0; i < epochLength + 1; i++) {
            std::vector<int> currentVertices = vertices;

            if (swapMethod == 's')
                ////2-changes
                shuffleTwoVertices(currentVertices);
            else
                ////changes road between
                shuffleRoadBetweenTwoVertices(currentVertices);

            int currentCost = calculateCost(matrix, currentVertices);
            int costDifference = cost - currentCost;

            if (costDifference > 0 || makeDecision(costDifference, currHeat)) {
                cost = currentCost;
                vertices = currentVertices;

                if (currentCost < bestCost) {

                    bestCost = currentCost;
                    bestSolution = currentVertices;
                }
            }
        }

        if (coolMethod == 'g')
            ////geometric
            currHeat *= pow(coolingRate, epoch);
        else
            ////logarithmic
            currHeat /= (1 + log(1 + epoch));
    }

    return new Path(bestSolution, bestCost);
}

int SimulatedAnnealing::calculateCost(AdjacencyMatrix &matrix, std::vector<int> &vertices) {
    int resultCost = 0;
    int instanceSize = matrix.getCitiesNumber() - 1;

    for (int i = 0; i < instanceSize; i++) {
        resultCost += matrix.getCost(vertices.at(i), vertices.at(i+1));
    }
    resultCost += matrix.getCost(vertices.at(instanceSize), vertices.at(0));

    return resultCost;
}

void SimulatedAnnealing::fullShuffle(std::vector<int> &vertices) {
    for (int i = 0; i < vertices.size(); i++) {
        int firstIndex = RandomGenerator::getInt(vertices.size() - 1);
        int secondIndex = RandomGenerator::getInt(vertices.size() - 1);

        std::swap(vertices[firstIndex], vertices[secondIndex]);
    }
}

void SimulatedAnnealing::shuffleTwoVertices(std::vector<int> &vertices) {
    int firstIndex = RandomGenerator::getInt(vertices.size() - 1);
    int secondIndex = RandomGenerator::getInt(vertices.size() - 1);

    std::swap(vertices[firstIndex], vertices[secondIndex]);
}

void SimulatedAnnealing::shuffleRoadBetweenTwoVertices(std::vector<int> &vertices) {
    int firstIndex = RandomGenerator::getInt(vertices.size() - 1);
    int secondIndex = RandomGenerator::getInt(vertices.size() - 1);

    if (secondIndex < firstIndex)
        std::swap(vertices[firstIndex], vertices[secondIndex]);

    while (firstIndex < secondIndex)
    {
        std::swap(vertices[firstIndex], vertices[secondIndex]);
        firstIndex++;
        secondIndex--;
    }
}

bool SimulatedAnnealing::makeDecision(int difference, double heat) {
    return RandomGenerator::getDouble(1) < exp(difference / heat);
}