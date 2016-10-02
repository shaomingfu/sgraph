#include "position.h"
#include <cstdio>
#include <sstream>

position::position(const string &s)
{
	char line[1024000];
	stringstream sstr(s);
	sstr >> label >> line;
	sstr >> px >> py >> pz >> line;
	sstr >> pp >> pred;
}

int position::print()
{
	printf("%d -> %.2lf %.2lf %.2lf -> %.2lf %d\n", label, px, py, pz, pp, pred);
	return 0;
}
