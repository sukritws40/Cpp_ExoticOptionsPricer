#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

//input valid For double that can be negative; such as risk free
double negative_check(string x);

//Unsigned long input valid for number of path
unsigned long unsignedlong_check(string x);

int basket_check(string x);

//input valid For double that cannot be negative; such as risk free
double double_check(string x);

//Mode Select
string SelectMode();


//Option Select
string SelectOption();

string SelectProcess();

double corr_check(string x);