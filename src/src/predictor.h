#ifndef __PREDICTOR_H__
#define __PREDICTOR_H__

#include <vector>
#include "block.h"

using namespace std;

class predictor
{
public:
	vector<block> blocks;

public:
	int load(const string &file);
	int predict();
	int write();
};

#endif
