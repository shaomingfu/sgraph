#ifndef __SAMPLE_H__
#define __SAMPLE_H__

#include "position.h"
#include <vector>

using namespace std;

class sample
{
public:
	vector<position> positions;
	double abdratio;

public:
	int add_position(const string &s);
	int process();
	int print(int index);
	int clear();
	bool boundary();

private:
	int assess_abundance();
};

#endif
