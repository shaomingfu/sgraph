#include "position.h"
#include <cstdio>
#include <sstream>
#include <cmath>

position::position(const string &s)
{
	char line[1024000];
	stringstream sstr(s);
	sstr >> pred;
	pred = exp(pred);
}

int position::print()
{
	printf("pred = %.3lf  (%d %.3lf %.3lf %d)\n", pred, tlab, rabd, tabd, alab);
	return 0;
}
