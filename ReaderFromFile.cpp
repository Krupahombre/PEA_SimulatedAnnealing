#include "ReaderFromFile.h"

#include <iostream>
#include <string>
#include <fstream>

using namespace std;

ReaderFromFile::ReaderFromFile()
{
    option = ' ';
    numberOfVertices = 0;
    filename = "Brak wczytanego pliku";
}


ReaderFromFile::~ReaderFromFile()
{
    if (numberOfVertices != 0) {
        for (int i = 0; i < numberOfVertices; i++)
            delete vertices[i];
        delete[] vertices;
        vertices = NULL;
        numberOfVertices = 0;
    }
}


int ReaderFromFile::LoadFile(string &filename) {

    /*if (numberOfVertices != 0) {
        for (int i = 0; i < numberOfVertices; i++)
            delete vertices[i];
        delete[] vertices;
        vertices = NULL;
        numberOfVertices = 0;
    }*/
    string fileExt = filename.substr(filename.find_last_of(".") + 1);
    if (fileExt != "txt" && fileExt != "tsp" && fileExt != "atsp") //dodanie do nazwy pliku rozszerzenia .txt gdy go nie ma
    {
        filename += ".txt";
    }
    fileExt = filename.substr(filename.find_last_of(".") + 1);

    if (fileExt == "txt") {
        return ReaderFromFile::LoadFileTXT(filename);
    }

    if (fileExt == "tsp") {
        return ReaderFromFile::LoadFileTSP(filename);
    }

    if (fileExt == "atsp") {
        return ReaderFromFile::LoadFileATSP(filename);
    }

    return 0;
}

int ReaderFromFile::LoadFileTXT(std::string & filename)
{
    fstream File;
    File.open(filename, ios::in);
    if (!File.good()) {
        this->filename = "Brak wczytanego pliku";
        cout << "\nNie mozna wczytac pliku!\n";
        return 0;
    }

    if (numberOfVertices != 0) {
        for (int i = 0; i < numberOfVertices; i++)
            delete[] vertices[i];
        delete[] vertices;
        vertices = NULL;
        numberOfVertices = 0;
    }

    this->filename = filename;
    File >> numberOfVertices;
    vertices = new int*[numberOfVertices];
    int line = 0;

    for (int i = 0; i < numberOfVertices; i++)
        vertices[i] = new int[numberOfVertices];

    while (!File.eof()) {
        for (int i = 0; i < numberOfVertices; i++) {
            for (int j = 0; j < numberOfVertices; j++) {
                File >> vertices[i][j];
            }

            line++;
        }
    }
    File.close();

    if (line != numberOfVertices && line != numberOfVertices * 2) { // zabezpieczenie pir
        cout << "-> Zla ilosc danych <-\n";
        this->filename = "Brak wczytanego pliku";
        for (int i = 0; i < numberOfVertices; i++)
            delete[] vertices[i];
        delete[] vertices;
        vertices = NULL;
        numberOfVertices = 0;
        return 1;
    }
    cout << "\nFile has been read!\n";
    return 0;
}

int ReaderFromFile::LoadFileTSP(std::string & filename)
{
    ifstream File;
    File.open(filename, ios::in);
    if (!File.good()) {
        this->filename = "Brak wczytanego pliku";
        cout << "\nNie mozna wczytac pliku!\n";
        return 0;
    }
    this->filename = filename;

    if (numberOfVertices != 0) {
        for (int i = 0; i < numberOfVertices; i++)
            delete vertices[i];
        delete[] vertices;
        vertices = NULL;
        numberOfVertices = 0;
    }

    string line;
    while (!File.eof()) {
        getline(File, line);
        {
            if (!line.compare(0, 6, "TYPE: ")) {
                if (!line.compare(7, 3, "TSP")) {
                    cout << "\n To nie jest plik TSP\n"; // czy typ pliku to TSP
                    return 1;
                }

            }
            else if (!line.compare(0, 7, "TYPE : ")) {
                if (!line.compare(8, 3, "TSP")) {
                    cout << "\n To nie jest plik TSP\n"; // czy typ pliku to TSP
                    return 1;
                }
            }

            if (!line.compare(0, 11, "DIMENSION: ")) {
                string number = line.substr(11, 100);
                numberOfVertices = stoi(number); //zapisanie ilo�ci wierzcho�k�w
            }
            else if (!line.compare(0, 12, "DIMENSION : ")) {
                string number = line.substr(12, 100);
                numberOfVertices = stoi(number); //zapisanie ilo�ci wierzcho�k�w
            }


            if (!line.compare(0, 18, "EDGE_WEIGHT_TYPE: ")) {
                if (!line.compare(19, 8, "EXPLICIT")) {
                    cout << "\n Nieobslugiwany typ danych\n"; // czy zapisano jako wagi kraw�dzi
                    return 1;
                }
            }
            else if (!line.compare(0, 19, "EDGE_WEIGHT_TYPE : ")) {
                if (!line.compare(20, 8, "EXPLICIT")) {
                    cout << "\n Nieobslugiwany typ danych\n"; // czy zapisano jako wagi kraw�dzi
                    return 1;
                }
            }


            if (!line.compare(0, 20, "EDGE_WEIGHT_FORMAT: ")) { //Obs�uga r�nego typu zapisu macierzy
                if (!line.compare(20, 11, "FULL_MATRIX")) {

                    vertices = new int*[numberOfVertices];
                    for (int i = 0; i < numberOfVertices; i++)
                        vertices[i] = new int[numberOfVertices];

                    string temp;
                    while (!File.eof()) {
                        File >> temp;
                        if (temp == "EDGE_WEIGHT_SECTION") {
                            for (int j = 0; j < numberOfVertices; j++)
                                for (int k = 0; k < numberOfVertices; k++)
                                    File >> vertices[j][k];
                        }
                    }
                }
                else if (!line.compare(20, 14, "LOWER_DIAG_ROW")) {

                    vertices = new int*[numberOfVertices];
                    for (int i = 0; i < numberOfVertices; i++)
                        vertices[i] = new int[numberOfVertices];

                    string temp;
                    int line = 1;
                    while (!File.eof()) {
                        File >> temp;
                        if (temp == "EDGE_WEIGHT_SECTION") {
                            for (int j = 0; j < numberOfVertices; j++) {
                                for (int k = 0; k < line; k++) {
                                    File >> vertices[j][k];
                                    if (j != k)
                                        vertices[k][j] = vertices[j][k];
                                }
                                if (line < numberOfVertices)
                                    line++;
                            }

                        }
                    }
                }
                else if (!line.compare(20, 14, "UPPER_DIAG_ROW")) {

                    vertices = new int*[numberOfVertices];
                    for (int i = 0; i < numberOfVertices; i++)
                        vertices[i] = new int[numberOfVertices];

                    string temp;
                    int line = numberOfVertices-1;
                    while (!File.eof()) {
                        File >> temp;
                        if (temp == "EDGE_WEIGHT_SECTION") {
                            for (int j = numberOfVertices-1; j >= 0; j--) {
                                for (int k = line; k >= 0; k--) {
                                    File >> vertices[j][k];
                                    if (j != k)
                                        vertices[k][j] = vertices[j][k];
                                }
                                if (line >= 0)
                                    line--;
                            }
                        }
                    }
                }
                else {
                    cout << "\nNieobslugiwany format macierzy\n";
                    return 1;
                }
            }

            else if (!line.compare(0, 21, "EDGE_WEIGHT_FORMAT : ")) { //Obs�uga r�nego typu zapisu macierzy
                if (!line.compare(21, 11, "FULL_MATRIX")) {

                    vertices = new int*[numberOfVertices];
                    for (int i = 0; i < numberOfVertices; i++)
                        vertices[i] = new int[numberOfVertices];

                    string temp;
                    while (!File.eof()) {
                        File >> temp;
                        if (temp == "EDGE_WEIGHT_SECTION") {
                            for (int j = 0; j < numberOfVertices; j++)
                                for (int k = 0; k < numberOfVertices; k++)
                                    File >> vertices[j][k];
                        }
                    }
                }
                else if (!line.compare(21, 14, "LOWER_DIAG_ROW")) {

                    vertices = new int*[numberOfVertices];
                    for (int i = 0; i < numberOfVertices; i++)
                        vertices[i] = new int[numberOfVertices];

                    string temp;
                    int line = 1;
                    while (!File.eof()) {
                        File >> temp;
                        if (temp == "EDGE_WEIGHT_SECTION") {
                            for (int j = 0; j < numberOfVertices; j++) {
                                for (int k = 0; k < line; k++) {
                                    File >> vertices[j][k];
                                    if (j != k)
                                        vertices[k][j] = vertices[j][k];
                                }
                                if (line < numberOfVertices)
                                    line++;
                            }

                        }
                    }
                }
                else if (!line.compare(21, 14, "UPPER_DIAG_ROW")) {

                    vertices = new int*[numberOfVertices];
                    for (int i = 0; i < numberOfVertices; i++)
                        vertices[i] = new int[numberOfVertices];

                    string temp;
                    int line = numberOfVertices - 1;
                    while (!File.eof()) {
                        File >> temp;
                        if (temp == "EDGE_WEIGHT_SECTION") {
                            for (int j = numberOfVertices - 1; j >= 0; j--) {
                                for (int k = line; k >= 0; k--) {
                                    File >> vertices[j][k];
                                    if (j != k)
                                        vertices[k][j] = vertices[j][k];
                                }
                                if (line >= 0)
                                    line--;
                            }
                        }
                    }
                }
                else {
                    cout << "\nNieobslugiwany format macierzy\n";
                    return 1;
                }
            }
        }

    }
    File.close();
    cout << "\nPlik zostal wczytany!\n";
    return 0;
}

int ReaderFromFile::LoadFileATSP(std::string & filename)
{
    ifstream File;
    File.open(filename, ios::in);
    if (!File.good()) {
        this->filename = "Brak wczytanego pliku";
        cout << "\nNie mozna wczytac pliku!\n";
        return 0;
    }
    this->filename = filename;

    if (numberOfVertices != 0) {
        for (int i = 0; i < numberOfVertices; i++)
            delete vertices[i];
        delete[] vertices;
        vertices = NULL;
        numberOfVertices = 0;
    }

    string line;
    while (!File.eof()) {
        getline(File, line);
        {
            if (!line.compare(0, 6, "TYPE: "))
                if (!line.compare(7, 4, "ATSP")) {
                    cout << "\n To nie jest plik ATSP\n"; // czy typ pliku to ATSP
                    return 1;
                }

            if (!line.compare(0, 11, "DIMENSION: ")) {
                string number = line.substr(11, 100);
                numberOfVertices = stoi(number); //zapisanie ilo�ci wierzcho�k�w
            }
            if (!line.compare(0, 18, "EDGE_WEIGHT_TYPE: "))
                if (!line.compare(19, 8, "EXPLICIT")) {
                    cout << "\n Nieobslugiwany typ danych\n"; // czy zapisano jako wagi kraw�dzi
                    return 1;
                }
            if (!line.compare(0, 20, "EDGE_WEIGHT_FORMAT: ")) { //Obs�uga r�nego typu zapisu macierzy
                if (!line.compare(20, 11, "FULL_MATRIX")) {

                    vertices = new int*[numberOfVertices];
                    for (int i = 0; i < numberOfVertices; i++)
                        vertices[i] = new int[numberOfVertices];

                    string temp;
                    while (!File.eof()) {
                        File >> temp;
                        if (temp == "EDGE_WEIGHT_SECTION") {
                            for (int j = 0; j < numberOfVertices; j++)
                                for (int k = 0; k < numberOfVertices; k++)
                                    File >> vertices[j][k];
                        }
                    }
                }
                else {
                    cout << "\nNieobslugiwany format macierzy\n";
                    return 1;
                }
            }
        }

    }
    File.close();
    cout << "\nPlik zostal wczytany!\n";
    return 0;
}

int ReaderFromFile::GenerateMatrix(int numberOfVerts, bool sym)
{
    if (numberOfVertices != 0) {
        for (int i = 0; i < numberOfVertices; i++)
            delete vertices[i];
        delete[] vertices;
        vertices = NULL;
        numberOfVertices = 0;
    }

    this->numberOfVertices = numberOfVerts;
    this->filename = "Losowe dane - ";
    this->filename += to_string(numberOfVerts);

    vertices = new int*[numberOfVertices];
    for (int i = 0; i < numberOfVertices; i++)
        vertices[i] = new int[numberOfVertices];

    if (sym){
        int line = 1;
        for (int j = 0; j < numberOfVertices; j++) {
            for (int k = 0; k < line; k++) {
                vertices[j][k] = (rand() % 500) + 1;
                if (j != k)
                    vertices[k][j] = vertices[j][k];
                else if (j == k)
                    vertices[k][j] = -1;
            }
            if (line < numberOfVertices)
                line++;
        }
    }

    else {
        for (int i = 0; i < numberOfVertices; i++)
            for (int j = 0; j < numberOfVertices; j++) {
                if (i == j)
                    vertices[i][j] = -1;
                else
                    vertices[i][j] = (rand() % 500) + 1;
            }
    }


    return 0;
}
