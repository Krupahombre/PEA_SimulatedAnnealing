#pragma once

#include <random>

class RandomGenerator {
    static std::mt19937 gen;

public:
    static int getInt(int high);
    static int getInt(int low, int high);

    static double getDouble(double low, double high);
    static double getDouble(double high);
};
