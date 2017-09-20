#include "result_from_file.h"
#include "PayOff.h"
#include "NewProcessMC.h"
#include "show_result.h"

void result_basket(const Process& Process, vector<vector<double>> basket, vector<vector<double>> correlation, double strike, double r, double Expiry, unsigned long NumberOfPaths, int optionType)
{
    PayOff* thePayOff;
    if (optionType == 13)
    {
        thePayOff = new PayOffCall(strike);
        ProcessBasket theProcess(*thePayOff, Process,  basket, correlation, Expiry, r, NumberOfPaths);
		double result = theProcess();
		show_result_basket(basket, correlation, strike, r, Expiry, NumberOfPaths, optionType, result);
    }
    else  if (optionType == 14)
    {
        thePayOff = new PayOffPut(strike);
        ProcessBasket theProcess(*thePayOff, Process, basket, correlation, Expiry, r, NumberOfPaths);
		double result = theProcess();
		show_result_basket(basket, correlation, strike, r, Expiry, NumberOfPaths, optionType, result);
    }


}
void result_single_asset(const Process& Process,double Spot, double strike, double barrier, double Vol, double r, double Expiry,
                         double NumberOfIntervals, unsigned long NumberOfPaths, unsigned int optionType)
{
    PayOff* thePayOff;
    if (optionType == 1)
    {
        thePayOff = new PayOffCall(strike);
        ProcessEuro theProcess(*thePayOff, Process,Spot, r, Expiry, Vol, NumberOfPaths);
        double result = theProcess();
        show_result_single_asset(Spot, strike, barrier, Vol, r, Expiry, NumberOfIntervals, NumberOfPaths, optionType,result);
    }
    else if (optionType == 2)
    {
        thePayOff = new PayOffPut(strike);
        ProcessEuro theProcess(*thePayOff, Process,Spot, r, Expiry, Vol, NumberOfPaths);
        double result = theProcess();
        show_result_single_asset(Spot, strike, barrier, Vol, r, Expiry, NumberOfIntervals, NumberOfPaths, optionType,result);
    }
    else if (optionType == 3)
    {
        thePayOff = new PayOffCall(strike);
        ProcessAs theProcess(*thePayOff, Process,Spot, r, Expiry, Vol, NumberOfPaths, NumberOfIntervals);
        double result = theProcess();
        show_result_single_asset(Spot, strike, barrier, Vol, r, Expiry, NumberOfIntervals, NumberOfPaths, optionType,result);
    }
    else if (optionType == 4)
    {
        thePayOff = new PayOffPut(strike);
        ProcessAs theProcess(*thePayOff, Process,Spot, r, Expiry, Vol, NumberOfPaths, NumberOfIntervals);
        double result = theProcess();
        show_result_single_asset(Spot, strike, barrier, Vol, r, Expiry, NumberOfIntervals, NumberOfPaths, optionType,result);
    }
    else if (optionType == 5||optionType == 7||optionType == 9||optionType == 11)
    {
        thePayOff = new PayOffCall(strike);
        ProcessBarrier theProcess(*thePayOff, Process,strike, Spot, r, Expiry, Vol, barrier, optionType, NumberOfPaths, NumberOfIntervals);
        double result = theProcess();
        show_result_single_asset(Spot, strike, barrier, Vol, r, Expiry, NumberOfIntervals, NumberOfPaths, optionType,result);
    }
    else if (optionType == 6||optionType == 8||optionType == 10||optionType == 12)
    {
        thePayOff = new PayOffPut(strike);
        ProcessBarrier theProcess(*thePayOff, Process,strike, Spot, r, Expiry, Vol, barrier, optionType, NumberOfPaths, NumberOfIntervals);
        double result = theProcess();
        show_result_single_asset(Spot, strike, barrier, Vol, r, Expiry, NumberOfIntervals, NumberOfPaths, optionType,result);
    }
}
