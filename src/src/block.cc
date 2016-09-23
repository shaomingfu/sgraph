#include "block.h"
#include "config.h"
#include <cassert>
#include <binomial.h>

int block::index = 0;

int block::clear()
{
	chrm = "";
	pos = -1;
	s.clear();
	q.clear();
	return 0;
}

int block::predict()
{
	// TODO
	if(ltype == true) return 0;
	if(rtype == true) return 0;

	block::index++;
	printf("# sample-id = %d, length = %lu, location = %s:%d-%lu\n", block::index, s.size(), chrm.c_str(), pos, pos + s.size());

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

		int s1 = compute_binomial_score(n1 + n2, 0.5, n1);
		int s2 = compute_binomial_score(n1 + n2, 0.5, n2);

		double pseudo = 20;
		double p1 = (s1 + pseudo) / (s1 + s2 + 2.0 * pseudo);
		double p2 = (s2 + pseudo) / (s1 + s2 + 2.0 * pseudo);
		double pp3 = 1.0 - fabs(p2 - p1);
		double pp1 = p1 / (p1 + p2) * (1 - pp3);
		double pp2 = p2 / (p1 + p2) * (1 - pp3);

		printf("index = %d, label = %d, counts = (%d, %d), score = (%d, %d), pr = (%.5lf, %.5lf, %.5lf)\n", 
				index, labels[i], n1, n2, s1, s2, pp1, pp2, pp3);
	}

	return 0;
}

int block::predict0()
{
	// TODO
	if(ltype == true) return 0;
	if(rtype == true) return 0;

	block::index++;
	printf("# sample-id = %d, length = %lu, location = %s:%d-%lu\n", block::index, s.size(), chrm.c_str(), pos, pos + s.size());

	vector<int> ss(s.size());
	ss[0] = s[0];
	for(int i = 1; i < s.size(); i++) ss[i] = ss[i - 1] + s[i];

	vector<int> tt(s.size());
	tt[0] = ss[s.size() - 1];
	for(int i = 1; i < s.size(); i++) tt[i] = ss[s.size() - 1] - ss[i - 1];

	for(int i = 0; i < s.size(); i++)
	{
		int n1 = ss[i] / 750.0 + 1;
		int n2 = tt[i] / 750.0 + 1;

		double p1 = (i + 1) * 1.0 / (s.size() + 1);
		double p2 = (s.size() - i) * 1.0 / (s.size() + 1);

		int s1 = compute_binomial_score(n1 + n2, p1, n1);
		int s2 = compute_binomial_score(n1 + n2, p2, n2);

		printf("index = %d, label = %d, counts = (%d, %d), pr = (%.5lf, %.5lf), score = (%d, %d)\n", 
				index, labels[i], n1, n2, p1, p2, s1, s2);
	}

	return 0;
}

int block::evaluate(int a, int b, double &ave, double &dev)
{
	ave = dev = 0;
	if(a >= b) return 0;

	double sum = 0;
	for(int i = a; i < b; i++) sum += s[i];
	ave = sum / (b - a);

	double var = 0;
	for(int i = a; i < b; i++) var += (s[i] - ave) * (s[i] - ave);
	dev = sqrt(var / (b - a));

	return 0;
}

int block::build_feature_score(fscore &fs)
{
	fs.init(s.size());
	for(int i = fs.w; i < s.size() - fs.w; i++)
	{
		double ave1, ave2, dev1, dev2;
		evaluate(i - fs.w, i, ave1, dev1);
		evaluate(i, i + fs.w, ave2, dev2);

		int n1 = ave1 * fs.w / 75.0 + 1;
		int n2 = ave2 * fs.w / 75.0 + 1;
		fs.sa[i] = compute_binomial_score(n1 + n2, 0.5, n1);
		fs.sb[i] = compute_binomial_score(n1 + n2, 0.5, n2);
		fs.va[i] = dev1 / (ave1 + 1.0);
		fs.vb[i] = dev2 / (ave2 + 1.0);
	}
	return 0;
}

int block::build_labels(const set<int32_t> &ss, const set<int32_t> &tt)
{
	labels.clear();
	for(int i = 0; i < s.size(); i++)
	{
		int32_t p = i + pos;
		int label = 0;
		if(ss.find(p) != ss.end()) label = 1;
		if(tt.find(p) != tt.end()) label = -1;
		if(i == 0 && ltype == true) label = 1;
		if(i == s.size() - 1 && rtype == true) label = -1;
		labels.push_back(label);
	}
	return 0;
}

int block::build_features()
{
	fs20.w = 20;
	fs50.w = 50;
	fs100.w = 100;
	build_feature_score(fs20);
	build_feature_score(fs50);
	build_feature_score(fs100);

	return 0;
}

int block::write_samples()
{
	assert(s.size() == q.size());
	if(s.size() < min_sample_length) return 0;

	// TODO
	if(ltype == true) return 0;
	if(rtype == true) return 0;

	block::index++;
	printf("# sample-id = %d, length = %lu, location = %s:%d-%lu\n", block::index, s.size(), chrm.c_str(), pos, pos + s.size());

	// print label
	for(int i = 0; i < labels.size(); i++) printf("%d ", labels[i]); printf("\n");

	// print features
	for(int i = 0; i < s.size(); i++) printf("%d ", s[i]); printf("\n");
	for(int i = 0; i < q.size(); i++) printf("%.0lf ", q[i]); printf("\n");
	fs20.write();
	fs50.write();
	fs100.write();

	return 0;
}
