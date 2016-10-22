#include "sample.h"
#include "config.h"
#include <cstdio>
#include <cassert>
#include <algorithm>
#include <set>
#include <cmath>

int sample::add_position(const string &s)
{
	position p(s);
	positions.push_back(p);
	return 0;
}

int sample::clear()
{
	positions.clear();
	abdratio = 0;
	return 0;
}

int sample::process()
{
	assess_abundance();
	return 0;
}

int sample::assess_abundance()
{
	abdratio = 0;
	for(int i = 0; i < positions.size(); i++)
	{
		double tabd = positions[i].tabd + 1.0;
		double pabd = positions[i].pred + 1.0;
		abdratio += fabs(tabd - pabd) / tabd;
	}
	abdratio /= positions.size();
	return 0;
}

bool sample::boundary()
{
	for(int i = 0; i < positions.size(); i++)
	{
		if(positions[i].tabd < min_accept_expression) return false;
	}

	for(int i = 0; i < positions.size(); i++)
	{
		if(positions[i].tlab == 0) return true;
		if(positions[i].tlab == 2) return true;
	}
	return false;
}

int sample::print(int index)
{
	if(boundary() == false) return 0;

	printf("sample %d: positions = %lu, abd-ratio = %.3lf\n", index, positions.size(), abdratio);
	return 0;
}
