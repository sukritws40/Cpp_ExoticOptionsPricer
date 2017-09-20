#include "Process.h"
#include "BoxMuller.h"

#include <cmath>

ProcessGB::ProcessGB()
{
}

double ProcessGB::evolve(double Spot, double r, double Expiry, double Vol, double Random) const
{

	double variance = Vol*Vol*Expiry;
	double rootVariance = sqrt(variance);
	
	double itoCorrection = -0.5*variance;
	return Spot*exp((r * Expiry) + itoCorrection)* exp(rootVariance * Random);
}


ProcessBach::ProcessBach()
{
}

double ProcessBach::evolve(double Spot, double r, double Expiry, double Vol, double Random)const

{
	double variance = exp(((2 * r * Expiry) - 1) / (2 * r));
	double rootVariance = sqrt(variance);
	
	return Spot*exp(r * Expiry) + rootVariance*Random;
}