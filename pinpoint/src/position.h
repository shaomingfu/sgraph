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
	int label;		// trur label
	double xyz[3];	// prob for 0, 1, and 2
	double pp;		// largest prob
	int pred;		// predicted label
	double pabd;	// predicted abd

	// load from abundance file
	int tlab;		// true label
	double rabd;	// read abundance
	double tabd;	// true abundance
	int alab;		// abundance label

public:
	int assign_true_label();
	int print();
};

#endif
