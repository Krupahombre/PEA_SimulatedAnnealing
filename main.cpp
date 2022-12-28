#include <iostream>

#include "ReaderFromFile.h"
#include "SimulatedAnnealing.h"
#include "Timer.h"

////exe
int main() {
    ReaderFromFile readerFromFile;

    std::fstream configFile;
    std::fstream outputFile;

    configFile.open("../Data/config.ini", std::ios::in);
    outputFile.open("../Data/results_SA.csv", std::ios::out);

    std::string fileName;
    int repetitions;
    int optimalCost;

    double times = 0;
    int errors = 0;
    int epochLength;
    char swapMethod;
    char coolMethod;
    double coolingRate;
    int startTemperature;

    while (!configFile.eof()) {
        //odczyt
        configFile >> fileName;
        configFile >> repetitions;
        configFile >> optimalCost;
        configFile >> swapMethod;
        configFile >> coolMethod;
        configFile >> epochLength;
        configFile >> coolingRate;
        configFile >> startTemperature;

        //zapis
        outputFile << "Nazwa pliku" << ", ";
        outputFile << "Powtórzenia algorytmu" << ", ";
        outputFile << "Optymalny koszt" << "\n";

        outputFile << fileName << ", ";
        outputFile << repetitions << ", ";
        outputFile << optimalCost << "\n\n";

        outputFile << "Czasy wykonania [μs]" << ", ";
        outputFile << "Otrzymany koszt" << ", ";
        outputFile << "Błąd [%]" << ", ";
        outputFile << "Długość epoki" << "\n";

        readerFromFile.LoadFile(fileName);

        std::cout << "File : " << fileName << "\n";

        for (int j = 0; j < repetitions; j++) {

            SimulatedAnnealing sa;

            auto matrix = new AdjacencyMatrix(readerFromFile.numberOfVertices, readerFromFile.vertices);

            Timer t;

            auto resultPath = sa.executeSA(*matrix, epochLength, swapMethod, coolMethod, coolingRate, startTemperature);

            t.stop();

            times += t.getMicro();
            errors += ((resultPath->cost * 100) / optimalCost) - 100;

            outputFile << t.getMicro() << ", ";
            outputFile << resultPath->cost << ", ";
            outputFile << (((float)resultPath->cost * (float)100) / (float)optimalCost) - (float)100 << ", ";
            outputFile << epochLength << "\n";

            std::cout << "Time [micro]: " << t.getMicro() << "\n";

            std::cout << "Cost : " << resultPath->cost << "\n";

            std::cout << "Error [%] : " << (((float)resultPath->cost * (float)100) / (float)optimalCost) - (float)100 << "\n";
        }

        outputFile << "\nMetoda zamiany:" << " ,";
        outputFile << swapMethod << "\n";
        outputFile << "Schemat chłodzenia:" << " ,";
        outputFile << coolMethod << "\n";
        outputFile << "Współczynnik chłodzenia:" << " ,";
        outputFile << coolingRate << "\n";
        outputFile << "Temperatura początkowa:" << " ,";
        outputFile << startTemperature << "\n";
        outputFile << "Średni czas wykonania [μs]:" << " ,";
        outputFile << (times / repetitions) << "\n";
        outputFile << "Średni błąd [%]:" << " ,";
        outputFile << ((float)errors / (float)repetitions) << "\n\n";

        std::cout << "\nAvrage time [micro] : " << (times / repetitions) << std::endl;
        std::cout << "\nAvrage error [%] : " << ((float)errors / (float)repetitions) << std::endl << std::endl;

        times = 0;
        errors = 0;
    }

    configFile.close();
    outputFile.close();

    return 0;
}

////tests
//int main() {
//    ReaderFromFile readerFromFile;
//
//    std::fstream configFile;
//    std::fstream outputFile;
//
//    configFile.open("config.ini", std::ios::in);
//    outputFile.open("results_log_invert.csv", std::ios::out);
//
//    std::string fileName;
//    int repetitions;
//    int optimalCost;
//
//    double times = 0;
//    int errors = 0;
//    int epochs[] = v;
//
//    while (!configFile.eof()) {
//        //odczyt
//        configFile >> fileName;
//        configFile >> repetitions;
//        configFile >> optimalCost;
//
//        //zapis
//        outputFile << "Nazwa pliku" << ", ";
//        outputFile << "Powtórzenia algorytmu" << ", ";
//        outputFile << "Optymalny koszt" << "\n";
//
//        outputFile << fileName << ", ";
//        outputFile << repetitions << ", ";
//        outputFile << optimalCost << "\n\n";
//
//        outputFile << "Czasy wykonania [μs]" << ", ";
//        outputFile << "Otrzymany koszt" << ", ";
//        outputFile << "Błąd [%]" << ", ";
//        outputFile << "Długość epoki" << "\n";
//
//        readerFromFile.LoadFile(fileName);
//
//        std::cout << "File : " << fileName << "\n";
//
//        for (int k = 0; k < 6; k++) {
//
//            for (int j = 0; j < repetitions; j++) {
//
//                SimulatedAnnealing sa;
//
//                auto matrix = new AdjacencyMatrix(readerFromFile.numberOfVertices, readerFromFile.vertices);
//
//                Timer t;
//
//                auto resultPath = sa.executeSA(*matrix, epochs[k]);
//
//                t.stop();
//
//                times += t.getMicro();
//                errors += ((resultPath->cost * 100) / optimalCost) - 100;
//
//                outputFile << t.getMicro() << ", ";
//                outputFile << resultPath->cost << ", ";
//                outputFile << (((float)resultPath->cost * (float)100) / (float)optimalCost) - (float)100 << ", ";
//                outputFile << epochs[k] << "\n";
//
//                std::cout << "Time [micro]: " << t.getMicro() << "\n";
//
//                std::cout << "Cost : " << resultPath->cost << "\n";
//
//                std::cout << "Error [%] : " << (((float)resultPath->cost * (float)100) / (float)optimalCost) - (float)100 << "\n";
//            }
//
//            outputFile << "Średni czas wykonania [μs]:" << " ,";
//            outputFile << (times / repetitions) << "\n";
//            outputFile << "Średni błąd [%]:" << " ,";
//            outputFile << ((float)errors / (float)repetitions) << "\n\n";
//
//            std::cout << "\nAvrage time [micro] : " << (times / repetitions) << std::endl;
//            std::cout << "\nAvrage error [%] : " << ((float)errors / (float)repetitions) << std::endl << std::endl;
//
//            times = 0;
//            errors = 0;
//        }
//
//        times = 0;
//        errors = 0;
//    }
//
//    configFile.close();
//    outputFile.close();
//
//    return 0;
//}