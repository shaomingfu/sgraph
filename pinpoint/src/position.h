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

	// load from abundance file
	int tabd;		// true adb
	int pabd;		// predicted abd

public:
	int print();
};

#endif
