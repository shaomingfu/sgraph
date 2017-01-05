#ifndef __MWU_H__
#define __MWU_H__

#include <vector>

using namespace std;

string vector2string(const vector<int> &x);
int compute_mann_whitney_pvalue(const vector<int> &x, const vector<int> &y, double &left, double &right);
int test_mwu();

#endif
