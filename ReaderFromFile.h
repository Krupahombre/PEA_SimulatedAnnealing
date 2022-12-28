#pragma once

#include <iostream>
#include <fstream>

class ReaderFromFile {
public:
    char option;
    int numberOfVertices;
    int **vertices;

    bool configGood;
    std::string filename;

    ReaderFromFile();
    ~ReaderFromFile();

    int LoadFile(std::string &filename);
    int LoadFileTXT(std::string &filename);
    int LoadFileTSP(std::string &filename);
    int LoadFileATSP(std::string &filename);
    int GenerateMatrix(int numberOfVerts, bool sym);
};
