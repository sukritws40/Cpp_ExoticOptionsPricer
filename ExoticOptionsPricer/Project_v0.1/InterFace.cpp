#include <iostream>
#include <string>

#include "InputCheck.h"
#include "InputOption.h"
#include "PayOff.h"
#include "restart.h"
#include "NewProcessMC.h"
#include "Process.h"
#include "Portfolio.h"
#include "input_from_file.h"
using namespace std;

void InterFace()
{
	cout << "=======================================================================================================================" << endl;
	cout << "Please select mode" << endl;
	cout << "=======================================================================================================================" << endl;
	cout << "1. single option (manual input)" << endl;
	cout << "2. single option (input from file)" << endl;
	cout << "3. portfolio of option (input from file only)" << endl;
	cout << "4. exit" << endl;
	cout << "=======================================================================================================================\n" << endl;

}