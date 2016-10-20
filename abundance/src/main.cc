#include "pinpoint.h"

#include <fstream>
#include <string>
#include <iostream>
#include <cstdlib>

using namespace std;

int main(int argc, const char ** argv)
{
	if(argc != 3) 
	{
		printf("usage: %s: \n\
				<prediction-file> \n\
				<sample-file> \n", argv[0]);
		return 0;
	}

	pinpoint pp(argv[1], argv[2]);
	pp.solve();

	return 0;
}
