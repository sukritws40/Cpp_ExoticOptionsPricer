
#ifndef result_from_file_hpp
#define result_from_file_hpp

#include <vector>
#include "Process.h"
#include <stdio.h>

using namespace std;

void result_basket(const Process& Process, vector<vector<double>> basket, vector<vector<double>> correlation, double strike, double r, double Expiry, unsigned long NumberOfPaths, int optionType);

void result_single_asset(const Process& Process,double Spot, double strike, double barrier, double Vol, double r, double Expiry,
                         double NumberOfIntervals, unsigned long NumberOfPaths, unsigned int optionType);
#endif