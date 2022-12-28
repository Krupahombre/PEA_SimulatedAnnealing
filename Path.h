#pragma once

#include <string>
#include <vector>

class Path {
public:
    //Class variables
    std::vector<int> path;
    int cost;

    Path(const std::vector<int> & vertices, int cost);
    Path();
    ~Path();

    void addVertex(int vertex, int vertexCost); //adds vertex to path and updates cost with vertexCost
    void addVertex(int vertex);
    void setCost(int totalCost);

    std::string toString();
};
