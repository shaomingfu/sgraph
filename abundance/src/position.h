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
	// load from prediction file
	double pred;	// predicted abundance

	// load from abundance file
	int tlab;		// true label
	double rabd;	// read abundance
	double tabd;	// true abundance
	int alab;		// abundance label

public:
	int print();
};

#endif
