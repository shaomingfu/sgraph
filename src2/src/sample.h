#ifndef __SAMPLE_H__
#define __SAMPLE_H__

#include "position.h"
#include <vector>

using namespace std;

class sample
{
public:
	vector<position> positions;

public:
	int add_position(const string &s);
	int clear();
	int process();
};

#endif
