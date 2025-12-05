// bunch of libraries becuase I am unsure if i have too many dependancies here, but it naturally built up as problems arose.
#include <iostream>
#include <cmath>
#include <fstream>
#include <vector>
#include <string>
#include <utility>
#include <iomanip>

//header file name
#include "CustomFunctions.h"


//Main file start...
int main() {
    // start by locating the input file and asking the user for a number of lines to print as integer A, if the user says more than the number of rows available only five
    //will print and the max rows will be stated.
    std::string inputfile = "input2D_float.txt";

    double A;
    std::cout << "Specify the number of lines of this set you want to see: ";
    std::cin >> A;
    std::cout << "You asked for " << A << " lines!" << std::endl;

    // Read the data into a vector of pairs
    std::string filename = "input2D_float.txt";
    auto data = readData2D(filename);// function 1

    // Check if any data was read
    if (data.empty()) {
        std::cout << "No data read from file!" << std::endl;
        return -1;
    } else {
        std::cout << "File: " << inputfile << " successfully read!" << std::endl;
    }

    // Print the first A rows
    
    std::ofstream outfile("printpairs.txt");  // Open file

    printPairs(data, static_cast<size_t>(A),outfile);  // function 2
    printPairs(data, 10 , outfile);        // Prints 10 rows to screen + saves to file

   


    // Print the first A rows with magnitude
    printPairsWithMagnitude(data, static_cast<size_t>(A));  // function 3

    // Read the data from file
    
    

    // Read file
    auto data1 = readData2D(filename);
    size_t numRows = data.size();
    std::cout << "Number of rows with numbers in the file - this is used for the Least Square calculations " << numRows << std::endl;
    
    // Extract columns
    auto X  = extractX(data1);
    auto Y  = extractY(data1);
    auto X2 = extractX2(data1);
    auto XY = extractXY(data1);

    // Print first 5 rows
    std::cout << "\nFirst 5 rows:\n";
    for (size_t i = 0; i < 5 && i < data1.size(); i++) {
        std::cout << "x=" << X[i]
                  << "   y=" << Y[i]
                  << "   x^2=" << X2[i]
                  << "   x*y=" << XY[i]
                  << std::endl;
    }

    // Compute sums
    double sum_x = 0.0, sum_y = 0.0, sum_xy = 0.0, sum_xsq = 0.0;
    for (double v : X)   sum_x   += v;
    for (double v : Y)   sum_y   += v;
    for (double v : XY)  sum_xy  += v;
    for (double v : X2)  sum_xsq += v;

    // Print sums
    std::cout << "sum_x   = " << sum_x   << std::endl;
    std::cout << "sum_y   = " << sum_y   << std::endl;
    std::cout << "sum_xy  = " << sum_xy  << std::endl;
    std::cout << "sum_xsq = " << sum_xsq << std::endl;

    //Formulas for Least Squares y = px + q
    double p = computeSlope(sum_x, sum_y, sum_xsq, sum_xy, numRows);
    double q = computeIntercept(sum_x, sum_y, sum_xsq, sum_xy, numRows);

    //print to user the answers
    std::cout << "Slope (p) = " << p << std::endl;
    std::cout << "Intercept (q) = " << q << std::endl;

    
    //create strings with these file names of the txt data files.
    std::string dataFile  = "input2D_float.txt";
    std::string errFile   = "error2D_float.txt";

    // Read data
    //auto data = readData2D(dataFile);
    /*
    auto X    = extractX(data);
    auto Y    = extractY(data);
    */

    // Read errors
    auto errors = readErrors(errFile);

    // Compute sums for least squares (assuming you already did this)
    
    
    for (size_t i = 0; i < numRows; i++) {
        sum_x   += X[i];
        sum_y   += Y[i];
        sum_xsq += X[i] * X[i];
        sum_xy  += X[i] * Y[i];
    }

    // Compute chi-squared
    double chi2 = computeChiSquared(X, Y, errors, p, q);

    std::cout << "Chi-squared = " << chi2 << std::endl;
// Chi^2 per Degrees of freedom , is chi squared value divided by the (number of values) * (parameter space)
    int k = 0;
std::cout << "Please enter number of  in your evaluation method (lst Sq = 2): ";
std::cin >> k;
double chi_sq_DOF = chi2 / (numRows - k);

//Tell the user what the anser to the chi sq DOF is...
std::cout << "The Chi squared degrees of freedom = " << chi_sq_DOF << std::endl;

// I started with slide 30 of Lecture 2 for this recursive function.
recursivePowPrint(X, Y,0);


    return 0;
}

// end of main file.

