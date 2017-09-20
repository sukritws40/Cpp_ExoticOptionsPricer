#include "input_valid_from_file.h"
#include <iostream>

using namespace std;

bool input_valid_from_file(double optionType,double x, int j)
{
	bool readgood = true;
	string input_name[9] = { "Option type","Spot price","Strike price","barrier","Volatility","Short rate","Year to expiry","Number of Intervals","Number of paths" };
	char s[80];
	sprintf(s, "%.7lf\n", x);
	double d = 0;
	int i;
	char c;
	char *step;
	if (j == 1 || j == 2 || j == 3 || j == 4 || j == 6)//check double type, cannot be negative
	{
		if (2 == sscanf(s, "%lf%c", &d, &c) && strtod(s, &step) >= 0)
		{
			if ('\n' == c) {
			}
		}
		else if ('\n' == s[strlen(s) - 1] || strtod(s, &step) < 0)
		{
			s[strlen(s) - 1] = 0;
			if (strtod(s, &step) < 0)
			{
				cout << input_name[j].c_str() << " cannot be negative number.";
				readgood = false;
				return readgood;
			}
			else
			{
				cout << input_name[j].c_str() << " should be a number.";
				readgood = false;
				return readgood;
			}
		}

	}
	if (j == 5)//check double type, can be negative
	{
		if (2 == sscanf(s, "%lf%c", &d, &c))
		{
			if ('\n' == c) {
			}

		}
		else if ('\n' == s[strlen(s) - 1])
		{
			cout << input_name[j].c_str() << " should be a number.";
			readgood = false;
			return readgood;
		}

	}

	if (j == 7 ) //unsigned long check
	{
		if (2 == sscanf(s, "%lf%c", &d, &c) && strtod(s, &step) >= 0)
		{
			if ('\n' == c) {
			}
			//check number of intervals for Asian and Barrier option
			if (optionType == 3 || optionType == 4 || optionType == 5 || optionType == 6 || optionType == 7 || optionType == 8 || optionType == 9 || optionType == 10 || optionType == 11 || optionType == 12)
			{
				if (strtod(s, &step) == 0)
				{
					cout << input_name[j].c_str() << " cannot be 0.";
					readgood = false;
					return readgood;
				}
			}
		}
		else if ('\n' == s[strlen(s) - 1] || strtod(s, &step) < 0)
		{
			s[strlen(s) - 1] = 0;
			if (strtod(s, &step) < 0)
			{
				cout << input_name[j].c_str() << " cannot be negative number.";
				readgood = false;
				return readgood;
			}
			else
			{
				cout << input_name[j].c_str() << " should be a number.";
				readgood = false;
				return readgood;
			}
		}
	}
	if (j == 8) //unsigned long check
	{
		if (2 == sscanf(s, "%d%c", &i, &c) && strtod(s, &step) > 0)
		{
			if ('\n' == c) {
			}
			//check number of intervals for Asian and Barrier option
		}
		else if ('\n' == s[strlen(s) - 1] || strtod(s, &step) < 0)
		{
			s[strlen(s) - 1] = 0;
			if (strtod(s, &step) < 0)
			{
				cout << input_name[j].c_str() << " cannot be negative number.";
				readgood = false;
				return readgood;
			}
			else if (strtod(s, &step) == 0)
			{
				cout << input_name[j].c_str() << " cannot be 0.";
				readgood = false;
				return readgood;
			}
			else
			{
				cout << input_name[j].c_str() << " should be a integer.";
				readgood = false;
				return readgood;
			}
		}
	}
	return readgood;
}