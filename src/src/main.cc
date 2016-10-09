#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <iostream>
#include <ctime>

#include "assembler.h"
#include "config.h"
#include "predictor.h"

using namespace std;

int main(int argc, const char **argv)
{
	if(argc == 5)
	{
		assembler asmbl(argv[2]);
		asmbl.process(argv[1], argv[3], argv[4]);
	}

	if(argc == 2)
	{
		predictor p;
		p.process(argv[1]);
	}

    return 0;
}
