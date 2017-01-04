#ifndef __BLOCK_H__
#define __BLOCK_H__

#include <string>
#include <vector>
#include <set>

#include "fscore.h"

using namespace std;

class block
{
public:
	static int index;

	vector<int> labels;	// labels
	vector<int> abd;	// real abundance

	// features
	vector<int> s;		// abundance
	vector<double> q;	// ave-quality
	fscore fs20;		// window 20 scores
	fscore fs50;		// window 50 scores
	fscore fs100;		// window 100 scores

	// native prediction
	vector<double> pr1;		// probablity of being start
	vector<double> pr2;		// probablity of being end
	vector<double> pr3;		// probablity of being middle

public:
	int predict();
	int evaluate(int s, int t, double &ave, double &dev);
};

#endif
