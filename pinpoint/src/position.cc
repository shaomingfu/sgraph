#include "position.h"
#include <cstdio>
#include <sstream>

position::position(const string &s)
{
	char line[1024000];
	stringstream sstr(s);
	sstr >> label >> line;
	sstr >> xyz[0] >> xyz[1] >> xyz[2] >> line;
	sstr >> pp >> pred;
}

int position::print()
{
	printf("%d -> %.2lf %.2lf %.2lf -> %.2lf %d, predicted abd = %d, true abd = %d\n", 
			label, xyz[0], xyz[1], xyz[2], pp, pred, tabd, pabd);
	return 0;
}
