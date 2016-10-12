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

	int correct0;
	int correct1;
	int correct2;
	int label0;
	int label1;
	int label2;
	int predict0;
	int predict1;
	int predict2;

	int nsample;
	double abdratio;

public:
	int solve();
	int load_prediction();
	int load_abundance();
	bool process();
};

#endif
