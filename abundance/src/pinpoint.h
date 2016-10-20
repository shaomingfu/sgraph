#ifndef __PINPOINT_H__
#define __PINPOINT_H__

#include "sample.h"
#include <string>
#include <vector>
#include <fstream>

using namespace std;

class pinpoint
{
public:
	pinpoint(const string &prd_file, const string &abd_file);
	~pinpoint();

public:
	ifstream fprd;
	ifstream fabd;

	sample sp;
	int index;

	int nsample;
	double abdratio;

public:
	int solve();
	int load_prediction();
	int load_abundance();
	bool process();
};

#endif
