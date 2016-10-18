#include "position.h"
#include <cstdio>
#include <sstream>
#include <cassert>
#include <cmath>

position::position(const string &s)
{
	char line[1024000];
	stringstream sstr(s);
	sstr >> label >> line;
	sstr >> xyz[0] >> xyz[1] >> xyz[2] >> line;
	sstr >> pp >> pred >> pabd;
	pabd = exp(pabd);
}

int position::assign_true_label()
{
	if(tlab == 0) label = 1;
	else if(tlab == 1) label = 2;
	else if(tlab == -1) label = 0;
	else assert(false);
	return 0;
}

int position::print()
{
	printf("%d -> %.2lf %.2lf %.2lf -> %.2lf %d, %.3lf (%d %.3lf %.3lf %d)\n", 
			label, xyz[0], xyz[1], xyz[2], pp, pred, pabd, tlab, rabd, tabd, alab);
	return 0;
}
