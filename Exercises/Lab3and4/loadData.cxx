#include <iostream>
#include <string>
#include <vector>
#include "FiniteFunctions.h"
#include <filesystem> //To check extensions in a nice way

#include "gnuplot-iostream.h" //Needed to produce plots (not part of the course) 

using std::filesystem::path;

//Code to load !


std::vector<double> loadDataFromFile(const std::string &filename) {
    std::vector<double> data;
    std::ifstream infile(filename);

    if (!infile.is_open()) {
        std::cerr << "ERROR: Cannot open file " << filename << std::endl;
        return data;
    }

    double value;
    while (infile >> value) {
        data.push_back(value);
    }

    return data;
}





