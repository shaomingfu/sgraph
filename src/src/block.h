#ifndef __BLOCK_H__
#define __BLOCK_H__

#include <string>
#include <vector>
#include <set>

using namespace std;

class block
{
public:
	string chrm;
	int32_t pos;
	vector<int> s;		// abundance
	vector<double> q;	// ave-quality
	static int index;
	bool ltype;
	bool rtype;

public:
	int clear();
	int build_samples(const set<int32_t> &ss, const set<int32_t> &tt);
};

#endif
