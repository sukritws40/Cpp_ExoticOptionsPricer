#ifndef ProcessMC_hpp
#define ProcessMC_hpp

#include <stdio.h>
#include "BoxMuller.h"
#include "PayOff.h"
#include <vector>
#include "Process.h"

using namespace std;

class ProcessMc
{
public:
	ProcessMc() {};
	virtual double operator()() const = 0;
	virtual ~ProcessMc() {}
private:
};

class ProcessEuro : public ProcessMc
{
public:
	ProcessEuro(const PayOff& thePayOff_,
		const Process& theProcess_,
		double Spot_,
		double r_,
		double Expiry_,
		double Vol_,
		unsigned long NumberOfPaths_);
	virtual double operator()() const;
	virtual ~ProcessEuro() {}
private:
	const PayOff& thePayOff;
	const Process& theProcess;
	double Spot;
	double r;
	double Expiry;
	double Vol;
	unsigned long NumberOfPaths;
};

class ProcessAs : public ProcessMc
{
public:
	ProcessAs(const PayOff& thePayOff_,
		const Process& theProcess_,
		double Spot_,
		double r_,
		double Expiry_,
		double Vol_,
		unsigned long NumberOfPaths_,
		double NumberOfIntervals_);
	virtual double operator()() const;
	virtual ~ProcessAs() {}
private:
	const PayOff& thePayOff;
	const Process& theProcess;
	double Spot;
	double r;
	double Expiry;
	double Vol;
	unsigned long NumberOfPaths;
	double NumberOfIntervals;
};

class ProcessBarrier : public ProcessMc
{
public:
	ProcessBarrier(const PayOff& thePayOff_,
		const Process& theProcess_,
		double strike_,
		double Spot_,
		double r_,
		double Expiry_,
		double Vol_,
		double barrier_,
		double option_,
		unsigned long NumberOfPaths_,
		double NumberOfIntervals_);
	virtual double operator()() const;
	virtual ~ProcessBarrier() {}
private:
	const PayOff& thePayOff;
	const Process& theProcess;
	double strike;
	double Spot;
	double r;
	double Expiry;
	double Vol;
	double barrier;
	double option;
	unsigned long NumberOfPaths;
	double NumberOfIntervals;
};

class ProcessBasket : public ProcessMc
{
public:
	ProcessBasket(
		const PayOff& thePayOff_,
		const Process& theProcess_,
		vector<vector<double>> basket_,
		vector<vector<double>> correlation_,
		double Expiry_,
		double r_,
		unsigned long NumberOfPaths_);
	virtual double operator()() const;
	virtual ~ProcessBasket() {}
private:
	const PayOff& thePayOff;
	const Process& theProcess;
	vector<vector<double>> basket;
	vector<vector<double>> correlation;
	double Expiry;
	double r;
	unsigned long NumberOfPaths;
};



#endif