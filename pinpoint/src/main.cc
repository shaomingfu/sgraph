#include "pinpoint.h"
#include "config.h"

#include <fstream>
#include <string>
#include <iostream>
#include <cstdlib>

using namespace std;

int main(int argc, const char ** argv)
{
	if(argc != 8) 
	{
		printf("usage: %s: \n\
				<prediction-file> \n\
				<probability-threshold (for 0 and 2)> \n\
				<half-window-size-for-average (for 0 and 2)> \n\
				<half-window-size-for-correct (for 0 and 2)> \n\
				<probability-threshold (for 1)> \n\
				<half-window-size-for-computing-MIN (for 1)> \n\
				<abundance-file> \n", argv[0]);
		return 0;
	}

	min_prob = atof(argv[2]);
	block_size = 2 * atoi(argv[3]);
	max_correct_distance = 2 * atoi(argv[4]);

	min_prob1 = atof(argv[5]);
	block_size1 = atoi(argv[6]);

	pinpoint pp(argv[1], argv[7]);
	pp.solve();

	return 0;
}
