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
	double xyz[3];
	double pp;
	int pred;

public:
	int print();
};

#endif
