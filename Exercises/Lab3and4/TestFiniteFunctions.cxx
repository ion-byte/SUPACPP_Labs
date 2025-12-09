#include <iostream>
#include <string>
#include <vector>
#include "FiniteFunctions.h"
#include <filesystem> //To check extensions in a nice way
#include "gnuplot-iostream.h" //Needed to produce plots (not part of the course)
#include "FiniteFunctions.h"
#include "loadData.h"
using std::filesystem::path;


//Needed to load in data from other folder - expect big numbers from a never changing file name...
//std::vector<double> loadDataFromFile(const std::string &filename);

int main() {
    // Data folder is one level above
    std::vector<double> realData = loadDataFromFile("/workspaces/SUPACPP_Labs/Data/MysteryData20000.txt");

    if (realData.empty()) {
        std::cout << "Error: Could not load data!\n";
        return 1; // exit if file could not be read
    }

    FiniteFunction f(-5, 5, "MysteryDataPlotMallocFixed");

    f.plotFunction();                 // plot analytic function
    f.plotData(realData, 100, true);  // histogram of real data

    return 0;   // destructor of f will automatically generate Outputs/png/MysteryDataPlot.png
}


