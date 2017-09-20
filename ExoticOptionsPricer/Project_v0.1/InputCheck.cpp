#include "InputCheck.h"

using namespace std;

double negative_check(string x)
{
	char s[80];
	double d;
	char c;
	int a = 0;
	char *step;
	while (a<6)
	{
		cout << x.c_str() << ": ";
		fflush(stdout);
		rewind(stdin);
		fgets(s, 80, stdin);
		if (2 == sscanf_s(s, "%lf%c", &d, &c))
		{
			if ('\n' == c)
			{
				break;
			}
		}
		if ('\n' == s[strlen(s) - 1])
		{
			s[strlen(s) - 1] = 0;
			++a;
			if (a < 5)
			{

				cout << x.c_str() << " must be a number, please try again, " << 5 - a << " attempts left" << endl;

			}

			else
			{

				cout << x.c_str() << " must be a number, please try again, " << 5 - a << " attempts left" << endl;
				cout << "Error, running out of attempt" << endl;
				exit(0);



			}
		}
	}

	d = strtod(s, &step);
	return d;
}

unsigned long unsignedlong_check(string x)
{
	char s[80];
	double d;
	char c;
	int i;
	int a = 0;
	char *step;
	while (a<6) {
		cout << x.c_str() << ": ";
		fflush(stdout);
		rewind(stdin);
		fgets(s, 80, stdin);
		if (2 == sscanf_s(s, "%d%c", &i, &c) && strtod(s, &step) > 0)
		{
			if ('\n' == c)
			{
				break;
			}
		}
		if ('\n' == s[strlen(s) - 1] || strtod(s, &step) <= 0)
		{
			s[strlen(s) - 1] = 0;
			++a;
			if (a < 5)
			{
				if (strtoul(s, NULL, 0) <= 0)
				{
					cout << x.c_str() << " must be a positive number, please try again " << 5 - a << " attempts left" << endl;
				}

				else
				{
					cout << x.c_str() << " must be an integer, please try again " << 5 - a << " attempts left" << endl;
				}
			}

			else
			{
				if (strtoul(s, NULL, 0) <= 0)
				{
					cout << x.c_str() << " must be a positive number " << 5 - a << " attempts left" << endl;
				}

				else
				{
					cout << x.c_str() << " must be an integer, " << 5 - a << " attempts left" << endl;
				}
				
				cout << "Error, running out of attempt" << endl;
				exit(0);
			}
		}
	}

	d = strtoul(s, NULL, 0);
	return d;
}



double double_check(string x)
{
	char s[80];
	double d;
	char c;
	int a = 0;
	char *step;
	while (a<6)
	{
		cout << x.c_str() << ": ";
		fflush(stdout);
		rewind(stdin);
		fgets(s, 80, stdin);
		if (2 == sscanf_s(s, "%lf%c", &d, &c) && strtod(s, &step) > 0)
		{
			if ('\n' == c)
			{
				break;
			}
		}
		if ('\n' == s[strlen(s) - 1] || strtod(s, &step) <= 0)
		{
			s[strlen(s) - 1] = 0;
			++a;
			if (a < 5)
			{
				if (strtod(s, &step) <= 0)
				{
					cout << x.c_str() << " must be a positive number, please try again, " << 5 - a << " attempts left" << endl;
				}

				else
				{
					cout << x.c_str() << " must be a number, please try again, " << 5 - a << " attempts left" << endl;
				}
			}

			else
			{
				if (strtod(s, &step) <= 0)
				{
					cout << x.c_str() << " must be a positive number, " << 5 - a << " attempts left" << endl;
				}

				else
				{
					cout << x.c_str() << " must be a number, " << 5 - a << " attempts left" << endl;
					
				}
				
				cout << "Error, running out of attempt" << endl;
				exit(0);
			}
		}
	}

	d = strtod(s, &step);
	return d;
}



string SelectMode()
{
	string choice;

	int attempts = 4;
	for (; attempts >= 0; attempts--)
	{
		cin >> choice;

		if ((choice == "1" || choice == "2" || choice == "3" || choice == "4") && attempts >= 0)
		{
			return choice;
			break;
		}
		else if ((choice != "1" || choice != "2" || choice != "3" || choice != "4") && attempts == 0)
		{
			cout << "Error, run out of attempt. \n";
			exit(0);
		}
		else
		{
			cout << "Incorrect input, Please only enter 1, 2, 3 or 4 attempt left: " << attempts << endl;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}
	}

}

string SelectOption()
{
	string choice;

	int attempts = 4;
	for (; attempts >= 0; attempts--)
	{
		cin >> choice;

		if ((choice == "1" || choice == "2" || choice == "3" || choice == "4" || choice == "5" || choice == "6" || choice == "7" || choice == "8" || choice == "9" || choice == "10" || choice == "11" || choice == "12" || choice == "13" || choice == "14") && attempts >= 0)
		{
			return choice;
			break;
		}
		else if ((choice != "1" || choice != "2" || choice != "3" || choice != "4" || choice == "5" || choice == "6" || choice == "7" || choice == "8" || choice == "9" || choice == "10" || choice == "11" || choice == "12" || choice == "13" || choice == "14") && attempts == 0)
		{
			cout << "Error, run out of attempt. \n";
			exit(0);
		}
		else
		{
			cout << "Incorrect input, Please only enter 1 to 14, attempt left: " << attempts << endl;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}
	}

}

string SelectProcess()
{
	string choice;

	int attempts = 4;
	for (; attempts >= 0; attempts--)
	{
		cin >> choice;

		if ((choice == "1" || choice == "2") && attempts >= 0)
		{
			return choice;
			break;
		}
		else if ((choice != "1" || choice != "2") && attempts == 0)
		{
			cout << "Error, run out of attempt. \n";
			exit(0);
		}
		else
		{
			cout << "Incorrect input, Please only enter 1 or 2, attempt left: " << attempts << endl;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}
	}

}

double corr_check(string x)
{
	char s[80];
	double d;
	char c;
	int a = 0;
	char *step;
	while (a<6)
	{
		cout << x.c_str() << ": ";
		fflush(stdout);
		rewind(stdin);
		fgets(s, 80, stdin);
		if (2 == sscanf_s(s, "%lf%c", &d, &c) && strtod(s, &step) >= -1 && strtod(s, &step) <= 1)
		{
			if ('\n' == c)
			{
				break;
			}
		}
		if ('\n' == s[strlen(s) - 1] || strtod(s, &step) < -1 || strtod(s, &step) > 1)
		{
			s[strlen(s) - 1] = 0;
			++a;
			if (a < 5)
			{
				if (strtod(s, &step) < -1 || strtod(s, &step) > 1)
				{
					cout << x.c_str() << " Input must be in range of 1 and -1, please try again, " << 5 - a << " attempts left" << endl;
				}

				else
				{
					cout << x.c_str() << " Input must be in range of 1 and -1, please try again, " << 5 - a << " attempts left" << endl;
				}
			}

			else
			{
				if (strtod(s, &step) < -1 || strtod(s, &step) > 1)
				{
					cout << x.c_str() << " Input must be in range of 1 and -1, please try again, " << 5 - a << " attempts left" << endl;
				}

				else
				{
					cout << x.c_str() << " Input must be in range of 1 and -1, please try again, " << 5 - a << " attempts left" << endl;
					cout << "Error, running out of attempt" << endl;
					exit(0);

				}

			}
		}
	}

	d = strtod(s, &step);
	return d;
}