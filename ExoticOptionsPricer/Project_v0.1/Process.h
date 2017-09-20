#ifndef PROCESS_H
#define PROCESS_H

class Process
{
public:
	Process() {};
	virtual double evolve(double Spot, double r, double Expiry, double Vol, double Random) const = 0;
	virtual ~Process() {}


private:

};

class ProcessGB : public Process
{
public:

	ProcessGB();
	double evolve(double Spot, double r, double Expiry, double Vol, double Random) const;
	virtual ~ProcessGB() {}

private:

};


class ProcessBach : public Process
{
public:
	ProcessBach();
	double evolve(double Spot, double r, double Expiry, double Vol, double Random) const;
	virtual ~ProcessBach() {}

private:

};

#endif