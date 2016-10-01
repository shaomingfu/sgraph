#include "sample.h"
#include <cstdio>

int sample::add_position(const string &s)
{
	position p(s);
	positions.push_back(p);
	return 0;
}

int sample::clear()
{
	positions.clear();
	return 0;
}

int sample::process()
{
	for(int i = 0; i < positions.size(); i++)
	{
		printf("position %d: ");
		positions[i].print();
	}
	return 0;
}
