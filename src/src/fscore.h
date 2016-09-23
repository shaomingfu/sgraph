#ifndef __FSCORE_H__
#define __FSCORE_H__

#include <vector>

using namespace std;

class fscore
{
public:
	int w;
	vector<int> sa;
	vector<int> sb;
	vector<double> va;
	vector<double> vb;

public:
	int init(int k);
	int write();
};

#endif
