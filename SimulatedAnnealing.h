#pragma once

#include "AdjacencyMatrix.h"
#include "RandomGenerator.h"
#include "Path.h"
#include <climits>
#include <vector>

class SimulatedAnnealing {
public:
    ////tests only
    //double coolingRate = 0.999999;

    std::vector<int> bestSolution;
    int bestCost;
    int epoch;

    Path *executeSA(AdjacencyMatrix &matrix, int epochLength, char swapMethod, char coolMethod, double coolingRate, int startTemperature);
    int calculateCost(AdjacencyMatrix &matrix, std::vector<int> &vertices);
    void fullShuffle(std::vector<int> &vertices);
    void shuffleTwoVertices(std::vector<int> &vertices);
    void shuffleRoadBetweenTwoVertices(std::vector<int> &vertices);
    bool makeDecision(int difference, double heat);
};
