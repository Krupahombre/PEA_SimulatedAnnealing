#include "Path.h"

Path::Path() {
    path = std::vector<int>();
    cost = 0;
}

Path::Path(const std::vector<int> &vertices, int cost) : cost(cost) {
    //path = std::vector<int>();

    path = vertices;
}

Path::~Path() {
    path.clear();
}

void Path::addVertex(int vertex, int vertexCost) {
    path.push_back(vertex);
    cost += vertexCost;
}

void Path::addVertex(int vertex) {
    path.push_back(vertex);
}

void Path::setCost(int totalCost) {
    this->cost = totalCost;
}

std::string Path::toString() {
    std::string path_str;

    for (int iterator = 0; iterator < path.size(); iterator++) {
        auto vertex_str = std::to_string(path.at(iterator));

        path_str.append(vertex_str)
                .append(" -> ");
    }
    path_str.append(" end")
            .append("\nTotal cost: ")
            .append(std::to_string(cost));

    return path_str;
}