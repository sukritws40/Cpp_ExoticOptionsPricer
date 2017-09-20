#ifndef show_result_file_hpp
#define show_result_file_hpp

#include <vector>
#include <stdio.h>

using namespace std;

void show_result_basket( vector<vector<double>> basket, vector<vector<double>> correlation, double strike, double r, double Expiry, unsigned long NumberOfPaths, int optionType, double result);

void show_result_single_asset(double Spot, double strike, double barrier, double Vol, double r, double Expiry,double NumberOfIntervals, unsigned long NumberOfPaths, unsigned int optionType,double result);

#endif