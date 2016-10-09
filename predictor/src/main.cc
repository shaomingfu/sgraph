#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <iostream>
#include <ctime>

#include "predictor.h"

using namespace std;

int main(int argc, const char **argv)
{
	if(argc == 2)
	{
		predictor p;
		p.process(argv[1]);
	}

    return 0;
}
