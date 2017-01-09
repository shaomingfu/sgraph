#ifndef __BLOCK_H__
#define __BLOCK_H__

#include <string>
#include <vector>
#include <set>

#include "fscore.h"

using namespace std;

typedef pair<int, int> PI;

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

	vector<int> seqa;	// seqA
	vector<int> seqc;	// seqC
	vector<int> seqg;	// seqG
	vector<int> seqt;	// seqT

	vector<int> pstart;	// whether start
	vector<int> pend;	// whether end

	// native prediction
	vector<double> pr1;	// probablity of being start
	vector<double> pr2;	// probablity of being end
	vector<double> pr3;	// probablity of being middle

	vector<int> slist;	// predicted start boundaries
	vector<int> tlist;	// predicted end boundaries

	int start1;
	int start2;
	int start3;
	int end1;
	int end2;
	int end3;

public:
	int predict();
	int predict_with_binomial();
	int predict_with_mwu();
	int iterate(int a, int b);
	int split(int a, int b);
	int test_mwu(int a, int b, int k);
	bool verify_boundary(int x, const vector<int> &list);
	int filter_boundaries(vector<int> &list);
	int align_boundaries(int ff, const vector<int> &list, int &ncorrect, int &nlabel);
	int evaluate(int a, int b, double &ave, double &dev);
};

#endif
