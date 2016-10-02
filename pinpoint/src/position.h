#ifndef __POSITION_H__
#define __POSITION_H__

#include <vector>
#include <string>

using namespace std;

class position
{
public:
	position(const string &s);

public:
	int label;
	double px;
	double py;
	double pz;
	double pp;
	int pred;

public:
	int print();
};

#endif
