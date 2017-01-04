#ifndef __MWU_H__
#define __MWU_H__

#include <vector>

using namespace std;

string vector2string(const vector<int> &x);
double compute_mann_whitney_pvalue(const vector<int> &x, const vector<int> &y);
int test_mwu();

#endif
