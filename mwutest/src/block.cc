#include "block.h"
#include <cassert>
#include <cmath>
#include <cfloat>

int block::index = 0;

int block::predict()
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
