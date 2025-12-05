#ifndef CUSTOMFUNCTIONS_H
#define CUSTOMFUNCTIONS_H

#include <vector>
#include <string>
#include <utility>

//not much to say abou this file, it generally got in the way - as i kept putting actual functions here rather than the call - however I understand
// that by having the functions away from the header file, you can call those functions in other header files if you wish.

void printPairs(const std::vector<std::pair<double,double>>& data,
                size_t numLines,
                std::ofstream &outfile);


double mag(double x, double y);

std::vector<std::pair<double,double>> readDataFromFile(const std::string& filename);
//void printPairs(const std::vector<std::pair<double,double>>& data, size_t numLines);
void printPairsWithMagnitude(const std::vector<std::pair<double,double>>& data, size_t numLines);

// ----------------- Least Squares functions -----------------
std::vector<std::pair<double,double>> readData2D(const std::string& filename);

std::vector<double> extractX(const std::vector<std::pair<double,double>>& data);
std::vector<double> extractY(const std::vector<std::pair<double,double>>& data);
std::vector<double> extractX2(const std::vector<std::pair<double,double>>& data);
std::vector<double> extractXY(const std::vector<std::pair<double,double>>& data);

// ----------------- Chi-squared functions -----------------
double computeChiSquared(const std::vector<double>& X,
                         const std::vector<double>& Y,
                         const std::vector<double>& errors,
                         double p, double q);

std::vector<double> readErrors(const std::string& filename);

// Compute slope (p) for y = p*x + q
double computeSlope(double sum_x, double sum_y, double sum_xsq, double sum_xy, size_t numRows) {
    return (numRows * sum_xy - sum_x * sum_y) / (numRows * sum_xsq - sum_x * sum_x);
}

// Compute intercept (q) for y = p*x + q
double computeIntercept(double sum_x, double sum_y, double sum_xsq, double sum_xy, size_t numRows) {
    return (sum_xsq * sum_y - sum_xy * sum_x) / (numRows * sum_xsq - sum_x * sum_x);
}

double recursivePower(double base, int exp);

void recursivePowPrint(const std::vector<double>& X,
                       const std::vector<double>& Y,
                       size_t index = 0);

void saveLine(std::ofstream &outfile, const std::string &text, bool echoToScreen);



#endif
