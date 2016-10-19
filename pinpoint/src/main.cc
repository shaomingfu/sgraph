#include "pinpoint.h"
#include "config.h"

#include <fstream>
#include <string>
#include <iostream>
#include <cstdlib>

using namespace std;

int main(int argc, const char ** argv)
{
	if(argc != 6) 
	{
		printf("usage: %s: \n\
				<prediction-file> \n\
				<abundance-file> \n\
				<probability-threshold> \n\
				<half-window-size-for-average> \n\
				<min-accept-expression>\n", argv[0]);
		return 0;
	}

	min_prob = atof(argv[3]);
	block_size = 2 * atoi(argv[4]);
	min_accept_expression = atof(argv[5]);

	pinpoint pp(argv[1], argv[2]);
	pp.solve();

	return 0;
}
