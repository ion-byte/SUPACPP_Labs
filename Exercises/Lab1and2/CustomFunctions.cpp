#include <iostream>
#include <cmath>
#include <fstream>
#include <vector>
#include <string>
#include <utility>
#include <iomanip>
#include <sstream> // needed for stringstream


//Here are the functions that arecalled via the header file, I have left in some of functions I deleted out - so you can see there was a process of
//around attempting to make this work, especially with the savefile - where I only attempted it with the print pairs function.

void saveLine(std::ofstream &outfile, const std::string &text, bool echoToScreen = true) {
    if (echoToScreen)
        std::cout << text << std::endl;
    if (outfile.is_open())
        outfile << text << "\n";
}


// Magnitude function
double mag(double x, double y) {
    return std::sqrt(x*x + y*y);
}

// Updated readDataFromFile
std::vector<std::pair<double,double>> readDataFromFile(const std::string& filename) {
    std::vector<std::pair<double,double>> data;
    std::ifstream data_file(filename);
    if (!data_file.is_open()) {
        std::cout << "Error opening file: " << filename << std::endl;
        return data;
    }

    std::string line;

    // Skip the header line
    if (!std::getline(data_file, line)) {
        std::cout << "File is empty: " << filename << std::endl;
        return data;
    }

    // Read each line of data - discard the x and y from the first row :)
    while (std::getline(data_file, line)) {
        std::stringstream ss(line);
        double x, y;
        char comma;

        if (ss >> x >> comma >> y) {
            data.emplace_back(x, y);
        } else {
            std::cout << "  Non-numeric or malformed line ignored: " << line << std::endl;
        }
    }

    data_file.close();
    return data;
}

//back up function for print pairs while it try other things!
/*
// Print functions remain the same
void printPairs(const std::vector<std::pair<double,double>>& data, size_t numLines) {
    std::cout << "x,y" << std::endl; // header
    for (size_t i = 0; i < data.size() && i < numLines; i++) {
        std::cout << std::fixed << std::setprecision(6)
                  << data[i].first << "," << data[i].second << std::endl;
    }
}
*/

/*this has no save?
void printPairs(const std::vector<std::pair<double,double>>& data, size_t numLines) {
    std::cout << "x,y" << std::endl; // header

    // Check if user requested more rows than exist
    if (numLines > data.size()) {
        std::cout << "You asked for " << numLines << " rows, "
                  << "but the dataset only contains " << data.size() << " rows.\n";
        std::cout << "Showing only the first 5 rows instead:\n";

        size_t limit = std::min((size_t)5, data.size());
        for (size_t i = 0; i < limit; i++) {
            std::cout << std::fixed << std::setprecision(6)
                      << data[i].first << "," << data[i].second << std::endl;
        }
        return;
    }

    // Normal case: user request is valid
    for (size_t i = 0; i < numLines; i++) {
        std::cout << std::fixed << std::setprecision(6)
                  << data[i].first << "," << data[i].second << std::endl;
    }
}
*/

void printPairs(const std::vector<std::pair<double,double>>& data, 
                size_t numLines,
                std::ofstream &outfile)
{
    saveLine(outfile, "x,y"); // header

    // Check if user requested more rows than exist
    if (numLines > data.size()) {
        saveLine(outfile, "You asked for too many rows; showing first 5 rows instead:");
        size_t limit = std::min((size_t)5, data.size());
        for (size_t i = 0; i < limit; i++) {
            std::stringstream ss;
            ss << std::fixed << std::setprecision(6)
               << data[i].first << "," << data[i].second;
            saveLine(outfile, ss.str());
        }
        return;
    }

    // Normal case
    for (size_t i = 0; i < numLines; i++) {
        std::stringstream ss;
        ss << std::fixed << std::setprecision(6)
           << data[i].first << "," << data[i].second;
        saveLine(outfile, ss.str());
    }
}


/*
#include <fstream>
#include <sstream>

// Updated printPairs with file saving
void printPairs(const std::vector<std::pair<double,double>>& data,
                size_t numLines,
                std::ofstream &outfile) 
{
    // Header
    saveLine(outfile, "x,y");

    // Check if user requested more rows than exist
    if (numLines > data.size()) {
        std::stringstream ss;
        ss << "You asked for " << numLines << " rows, "
           << "but the dataset only contains " << data.size() << " rows.\n"
           << "Showing only the first 5 rows instead:";
        saveLine(outfile, ss.str());

        size_t limit = std::min((size_t)5, data.size());
        for (size_t i = 0; i < limit; i++) {
            std::stringstream line;
            line << std::fixed << std::setprecision(6)
                 << data[i].first << "," << data[i].second;
            saveLine(outfile, line.str());
        }
        return;
    }

    // Normal case: user request is valid
    for (size_t i = 0; i < numLines; i++) {
        std::stringstream line;
        line << std::fixed << std::setprecision(6)
             << data[i].first << "," << data[i].second;
        saveLine(outfile, line.str());
    }
}
*/



void printPairsWithMagnitude(const std::vector<std::pair<double,double>>& data, size_t numLines) {
    std::cout << "x,y,& magnitude" << std::endl;
    for (size_t i = 0; i < data.size() && i < numLines; i++) {
        double x = data[i].first;
        double y = data[i].second;
        double m = mag(x, y);
        std::cout << std::fixed << std::setprecision(6)
                  << x << "," << y << "," << m << std::endl;
    }
}

//Functions involving Lst Squares, Reading x,y and getting basic values to do least square fit with.
std::vector<std::pair<double,double>> readData2D(const std::string& filename) {
    std::vector<std::pair<double,double>> data;
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cout << "Error opening file: " << filename << std::endl;
        return data;
    }

    std::string line;
    std::getline(file, line); // skip header

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        double x, y;
        char comma;
        if (ss >> x >> comma >> y)
            data.emplace_back(x, y);
        else
            std::cout << "Skipping bad line: " << line << std::endl;
    }

    return data;
}

// Extract columns
std::vector<double> extractX(const std::vector<std::pair<double,double>>& data) {
    std::vector<double> X; X.reserve(data.size());
    for (const auto& p : data) X.push_back(p.first);
    return X;
}

std::vector<double> extractY(const std::vector<std::pair<double,double>>& data) {
    std::vector<double> Y; Y.reserve(data.size());
    for (const auto& p : data) Y.push_back(p.second);
    return Y;
}

std::vector<double> extractX2(const std::vector<std::pair<double,double>>& data) {
    std::vector<double> X2; X2.reserve(data.size());
    for (const auto& p : data) X2.push_back(p.first * p.first);
    return X2;
}

std::vector<double> extractXY(const std::vector<std::pair<double,double>>& data) {
    std::vector<double> XY; XY.reserve(data.size());
    for (const auto& p : data) XY.push_back(p.first * p.second);
    return XY;
}

double computeChiSquared(const std::vector<double>& X,
                         const std::vector<double>& Y,
                         const std::vector<double>& errors,
                         double p, double q)
{
    if (X.size() != Y.size() || X.size() != errors.size()) {
        std::cerr << "Error: vectors must have the same size!" << std::endl;
        return -1.0;
    }

    double chi2 = 0.0;
    for (size_t i = 0; i < X.size(); i++) {
        double model = p * X[i] + q;
        double diff  = Y[i] - model;
        chi2 += (diff * diff) / (errors[i] * errors[i]);
    }
    return chi2;
}

// Function to read errors from file
std::vector<double> readErrors(const std::string& filename) {
    std::vector<double> errs;
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error opening error file: " << filename << std::endl;
        return errs;
    }

    std::string line;
    // Optional: skip header if exists
    std::getline(file, line);

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        double e;
        if (ss >> e) {
            errs.push_back(e);
        } else {
            std::cout << "Skipping bad line in errors file: " << line << std::endl;
        }
    }
    return errs;
}


double recursivePower(double base, int exp) 
{
    if (exp < 0) {
        return 1.0 / recursivePower(base, -exp);
    }
    if (exp == 0) return 1.0;
    return base * recursivePower(base, exp - 1);
}


void recursivePowPrint(const std::vector<double>& X,
                       const std::vector<double>& Y,
                       size_t index)
{
    if (index >= X.size()) {
        std::cout << "Recursion complete!" << std::endl;
        return;
    }

    int exp = static_cast<int>(Y[index]);  // convert exponent to integer
    double result = recursivePower(X[index], exp);

    std::cout << "X[" << index << "]^Y[" << index << "] = "
              << result << std::endl;

    recursivePowPrint(X, Y, index + 1); // recursive call
}
