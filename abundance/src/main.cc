#include "pinpoint.h"
#include "config.h"

#include <fstream>
#include <string>
#include <iostream>
#include <cstdlib>

using namespace std;

int main(int argc, const char ** argv)
{
	if(argc != 4) 
	{
		printf("usage: %s: \n\
				<prediction-file> \n\
				<sample-file> \n\
				<min-accept-expression> \n", argv[0]);
		return 0;
	}

	min_accept_expression = atof(argv[3]);
	pinpoint pp(argv[1], argv[2]);
	pp.solve();

	return 0;
}
