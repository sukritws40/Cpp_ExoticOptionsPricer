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

int main()
{
	cout << "=======================================================================================================================" << endl;
	cout << "                                               Monte Carlo Option Pricer" << endl;
	cout << "=======================================================================================================================" << endl;
	cout << "Welcome to Monte Carlo Option Pricer\n" << endl;
	cout << "Please note that for single option input can be acquired by\n" << "> Manually type in the console\n" << "> From File in .txt format\n" << endl;
	cout << "PS. For Portfolio of Options your input must be a file in .txt format" << endl;

	bool r = true;
	while (r == true)
	{
		bool readgood = true;
		cout << "=======================================================================================================================" << endl;
		cout << "Please select mode" << endl;
		cout << "=======================================================================================================================" << endl;
		cout << "1. Single option (manual input)" << endl;
		cout << "2. Single option (input from file)" << endl;
		cout << "3. Portfolio of option (input from file)" << endl;             
		cout << "4. Exit" << endl;
		cout << "=======================================================================================================================\n" << endl;

		cout << "Mode: ";

		string mode = SelectMode();
		
		Process * pprocess;

		if (mode == "1")
		{
			cout << "\n=======================================================================================================================" << endl;
			cout << "Please select Process" << endl;
			cout << "=======================================================================================================================" << endl;
			cout << " 1.  Geometric Brownian Process" << endl;
			cout << " 2.  Bachelier Process" << endl;
			cout << "=======================================================================================================================\n" << endl;

			cout << "Process: ";
			string ProcessType = SelectProcess();

			cout << "Manual input mode" << endl;

			cout << "\n=======================================================================================================================" << endl;
			cout << "Please select option type" << endl;
			cout << "=======================================================================================================================" << endl;
			cout << " 1.  European Call Option" << endl;
			cout << " 2.  European Put Option" << endl;
			cout << " 3.  Asian Call Option" << endl;
			cout << " 4.  Asian Put Option" << endl;
			cout << " 5.  Up & In Barrier Call Option" << endl;
			cout << " 6.  Up & In Barrier Put Option" << endl;
			cout << " 7.  Up & Out Barrier Call Option" << endl;
			cout << " 8.  Up & Out Barrier Put Option" << endl;
			cout << " 9.  Down & In Barrier Call Option" << endl;
			cout << " 10. Down & In Barrier Put Option" << endl;
			cout << " 11. Down & Out Barrier Call Option" << endl;
			cout << " 12. Down & Out Barrier Put Option" << endl;
			cout << " 13. Basket Call Option" << endl;
			cout << " 14. Basket Put Option" << endl;
			cout << "=======================================================================================================================\n" << endl;

			cout << "Option type: ";
			string OptionType = SelectOption();

			
			double price = GetOptionInput(OptionType, ProcessType);

			cout << "=======================================================================================================================" << endl;
			cout << "price: " << price << endl;
			cout << "=======================================================================================================================" << endl;
		}

		else if (mode == "2")
		{
			cout << "\n=======================================================================================================================" << endl;
			cout << "Please select Process" << endl;
			cout << "=======================================================================================================================" << endl;
			cout << " 1.  Geometric Brownian Process" << endl;
			cout << " 2.  Bachelier Process" << endl;
			cout << "=======================================================================================================================\n" << endl;

			cout << "Process: ";
			string ProcessType = SelectProcess();

			if (ProcessType == "1")
			{
				pprocess = new ProcessGB;
			}
			else
			{
				pprocess = new ProcessBach;
			}

			cout << "=======================================================================================================================" << endl;
			cout << "Please enter your file name (with .txt)" << endl;
			cout << "Example: AsianCall.txt, AsianPut.txt, BasketCall.txt, BasketPut.txt " << endl;
			cout << "         Down&InCall.txt, Down&InPut.txt, Down&OutCall.txt, Down&OutPut.txt " << endl;
			cout << "         Up&InCall.txt, Up&InPut.txt, Up&OutCall.txt and Up&OutPut.txt " << endl;
			cout << "=======================================================================================================================" << endl;
			int i = 0;
			while (1)
			{
				cout << "File: ";
				string file;
				cin >> file;
				readgood = read_one_asset(*pprocess, file);
				if (readgood == false)
				{
					i += 1;
					cout << " Please input file agian, you have " << 5 - i << " times left." << endl;
				}
				else
					break;
				if (i == 5)
				{
					cout << "Error: Programme will exit" << endl;
					exit(EXIT_FAILURE);
				}

			}

		}

		else if (mode == "3")
		{
			cout << "\n=======================================================================================================================" << endl;
			cout << "Please select Process" << endl;
			cout << "=======================================================================================================================" << endl;
			cout << " 1.  Geometric Brownian Process" << endl;
			cout << " 2.  Bachelier Process" << endl;
			cout << "=======================================================================================================================\n" << endl;

			cout << "Process: ";
			string ProcessType = SelectProcess();

			if (ProcessType == "1")
			{
				pprocess = new ProcessGB;
			}
			else
			{
				pprocess = new ProcessBach;
			}

			cout << "=======================================================================================================================" << endl;
			cout << "Please enter your file name (with .txt)" << endl;
			cout << "Example: portfolio.txt" << endl;
			cout << "=======================================================================================================================" << endl;
			int i = 0;
			while (1)
			{
				cout << "File: ";
				string file;
				cin >> file;
				readgood = read_Portfolio(*pprocess,file);
				if (readgood == false)
				{
					i += 1;
					cout << " Please input file agian, you have " << 5 - i << " times left." << endl;
				}
				else
					break;
				if (i == 5)
				{
					cout << "Error: Programme will exit" << endl;
					exit(EXIT_FAILURE);
				}

			}
		}

		else
		{
			cout << "=======================================================================================================================" << endl;
			cout << "Thankyou for using our software." << endl;
			cout << "=======================================================================================================================" << endl;
			exit(0);
		}
		r = restart();
	}

}