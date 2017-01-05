#include "block.h"
#include "config.h"
#include "mwu.h"
#include <cassert>
#include <cmath>
#include <cfloat>
#include <algorithm>

int block::index = 0;

int block::predict()
{
	return predict_with_binomial();
}

int block::predict_with_mwu()
{
	iterate(0, s.size());

	if(pstart[0] == 1) blist.push_back(PI(0, START));
	if(pend[pend.size() - 1] == 1) blist.push_back(PI(pend.size() - 1, END));

	start1 = start2 = start3 = 0;
	end1 = end2 = end3 = 0;

	align_boundaries(START, start1, start3);
	align_boundaries(END, end1, end3);

	for(int i = 0; i < blist.size(); i++) 
	{
		if(blist[i].second == START) start2++;
		if(blist[i].second == END) end2++;
	}

	printf("sample %d: positions = %lu, START = %d / %d / %d, END = %d / %d / %d\n", 
			index,
			labels.size(), 
			start1, start2, start3,
			end1, end2, end3);

	return 0;
}

int block::split(int a, int b)
{
	assert(a >= 0 && a < s.size());
	assert(b >= 0 && b < s.size());
	if(b - a <= 20) return -1;

	double min_mse = DBL_MAX;
	int mink = -1;
	for(int k = a + 1; k < b; k++)
	{
		double ave1, dev1;
		double ave2, dev2;
		evaluate(a, k, ave1, dev1);
		evaluate(k, b, ave2, dev2);
		double var1 = dev1 * dev1 * (k - a);
		double var2 = dev2 * dev2 * (b - k);
		double mse = var1 + var2;
		if(mse >= min_mse) continue;
		min_mse = mse;
		mink = k;
	}
	return mink;
}

int block::test_mwu(int a, int b, int k)
{
	vector<int> v1;
	vector<int> v2;
	v1.push_back(s[a]);
	v2.push_back(s[k]);
	for(int i = a + 1; i < k; i++)
	{
		if(s[i] == v1.back()) continue;	
		v1.push_back(s[i]);
	}
	for(int i = k + 1; i < b; i++)
	{
		if(s[i] == v2.back()) continue;	
		v2.push_back(s[i]);
	}
	double left_pvalue, right_pvalue;
	compute_mann_whitney_pvalue(v1, v2, left_pvalue, right_pvalue);

	if(left_pvalue < max_mwu_pvalue) return START;
	if(right_pvalue < max_mwu_pvalue) return END;
	return MIDDLE;	
}

int block::iterate(int a, int b)
{
	if(b - a <= 20) return 0;
	int k = split(a, b);
	if(k < a || k >= b) return 0;
	int f = test_mwu(a, b, k);
	if(f == MIDDLE) return 0;

	blist.push_back(PI(k, f));

	int k1 = k, k2 = k;
	for(int k2 = k; k2 < b - 1; k2++) 
	{
		if(f == START && s[k2] > s[k2 + 1]) break;
		if(f == END && s[k2] < s[k2 + 1]) break;
	}
	for(int k1 = k; k1 >= a + 1; k1++)
	{
		if(f == START && s[k1 - 1] > s[k1]) break;
		if(f == END && s[k1 - 1] < s[k1]) break;
	}

	iterate(a, k1);
	iterate(k2, b);
	return 0;
}

int block::predict_with_binomial()
{
	block::index++;
	//printf("# sample-id = %d, length = %lu, location = %s:%d-%lu\n", block::index, s.size(), chrm.c_str(), pos, pos + s.size());
	printf("#-> %lu\n", s.size());

	for(int i = 0; i < s.size(); i++)
	{
		int k1 = i;
		int k2 = s.size() - i;
		int k = (k1 < k2) ? k1 : k2;
		if(k >= 100) k = 100;

		double ave1, ave2, dev1, dev2;
		evaluate(i - k, i, ave1, dev1);
		evaluate(i, i + k, ave2, dev2);

		int n1 = ave1 * k / 100 + 20;
		int n2 = ave2 * k / 100 + 20;

		int s1 = 999;
		int s2 = 999;
		//int s1 = compute_binomial_score(n1 + n2, 0.5, n1);
		//int s2 = compute_binomial_score(n1 + n2, 0.5, n2);

		double pseudo = 20;
		double p1 = (s1 + pseudo) / (s1 + s2 + 2.0 * pseudo);
		double p2 = (s2 + pseudo) / (s1 + s2 + 2.0 * pseudo);
		double pp3 = 1.0 - fabs(p2 - p1);
		double pp1 = p1 / (p1 + p2) * (1 - pp3);
		double pp2 = p2 / (p1 + p2) * (1 - pp3);

		/*
		printf("index = %d, label = %d, counts = (%d, %d), score = (%d, %d), pr = (%.5lf, %.5lf, %.5lf)\n", 
				index, labels[i], n1, n2, s1, s2, pp1, pp2, pp3);
		*/

		double pp = -1;
		int l1 = -1;

		if(pp1 >= pp2 && pp1 >= pp3)
		{
			l1 = 0;
			pp = pp1;
		}
		else if(pp2 >= pp3)
		{
			l1 = 2;
			pp = pp2;
		}
		else
		{
			l1 = 1;
			pp = pp3;
		}

		//int l0 = (labels[i] == 0) ? 1 : ((labels[i] == 1) ? 2 : 0);

		printf("%d -> %.6lf %.6lf %.6lf -> %.6lf %d\n", labels[i], pp1, pp3, pp2, pp, l1);
	}

	return 0;
}

int block::evaluate(int a, int b, double &ave, double &dev)
{
	ave = dev = 0;
	if(a >= b) return 0;

	double sum = 0;
	for(int i = a; i < b; i++)
	{
		//printf("a = %d, b = %d, i = %d, s.size() = %lu\n", a, b, i, s.size());
		assert(i >= 0 && i < s.size());
		sum += s[i];
	}

	ave = sum / (b - a);

	double var = 0;
	for(int i = a; i < b; i++) var += (s[i] - ave) * (s[i] - ave);
	dev = sqrt(var / (b - a));

	return 0;
}

int block::align_boundaries(int ff, int &ncorrect, int &nlabel)
{
	vector<PI> vv;
	for(int i = 0; i < labels.size(); i++)
	{
		if(labels[i] != ff) continue;
		vv.push_back(PI(i, -1));
	}
	nlabel = vv.size();
	ncorrect = 0;

	for(int i = 0; i < blist.size(); i++)
	{
		if(blist[i].second != ff) continue;
		vv.push_back(PI(blist[i].first, i));
	}

	sort(vv.begin(), vv.end());

	set<int> s;
	for(int i = 0; i < vv.size(); i++)
	{
		int p = vv[i].first;
		int k = vv[i].second;
		if(k == -1) continue;

		int p1 = max_correct_distance * 2;
		int p2 = max_correct_distance * 2;

		if(i >= 1 && vv[i - 1].second == -1 && s.find(i - 1) == s.end()) p1 = p - vv[i - 1].first;
		if(i < vv.size() - 1 && vv[i + 1].second == -1 && s.find(i + 1) == s.end()) p2 = vv[i + 1].first - p;

		if(p1 < max_correct_distance && p1 <= p2)
		{
			s.insert(i - 1);
			ncorrect++;
		}
		if(p2 < max_correct_distance && p2 < p1)
		{
			s.insert(i + 1);
			ncorrect++;
		}
	}
	return 0;
}


