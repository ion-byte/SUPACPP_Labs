// bunch of libraries becuase I am unsure of what I am doing - come back and remove unused.
#include<iostream>
#include<cmath>
#include<fstream>
#include<vector>
#include<string>
#include<utility>
#include<iomanip>

#include "CustomFunctions.h"


//Main code execution
int main(){
// create the variable that you will store the file with.
    std::string inputfile = "input2D_float.txt";

    //the pipe the data will go through is now connected and is called 'data_file'.
    std::ifstream data_file(inputfile);

    //Now the data that streams through the pipe needs to be stored somewhere, so this is created.
    std::vector<double> data;

    //check if the file opening has been successful.
    if (!data_file.is_open()) {
        std::cout<< "Error opening file: " << inputfile << std::endl;
        return -1;
    }
    else{
        std::cout <<"file: " << inputfile << " is open dude !" << std::endl;


    }

    double A;

    std::cout <<" Specify the number of lines of this set ya wanna see....";
    std::cin >> A;
    std::cout << "You asked for " <<A << " lines !" << std::endl;

    auto data = readDataFromFile(inputfile);
    printPairs(data, numLines);
    printPairsWithMagnitude(data, numLines);



data_file.close();
return 0;
}
