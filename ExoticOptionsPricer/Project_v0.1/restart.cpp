#include "restart.h"

using namespace std;

bool restart()
{
	string C;

	cout << "Do you want to Price another Option?" << endl;
	cout << "Please type Y or y to restart" << endl;
	cout << "Please type any other key to exit" << endl;
	cin >> C;

	if (C == "Y" || C == "y")
	{
		return true;
	}

	else
	{
		cout << "=======================================================================================================================" << endl;
		cout << "Thankyou for using our software." << endl;
		cout << "=======================================================================================================================" << endl;
		return false;
	}
}