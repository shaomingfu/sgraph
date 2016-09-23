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
	string chrm;
	int32_t pos;
	static int index;
	bool ltype;
	bool rtype;

	vector<int> labels;	// labels

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
	int clear();
	int predict();
	int predict0();
	int evaluate(int a, int b, double &ave, double &dev);
	int build_labels(const set<int32_t> &ss, const set<int32_t> &tt);
	int build_feature_score(fscore &fs);
	int build_features();
	int write_samples();
};

#endif
