#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <iostream>
#include <ctime>

#include "predictor.h"
#include "config.h"

using namespace std;

int main(int argc, const char **argv)
{
	if(argc == 4)
	{
		predictor p;
		max_mwu_pvalue = atof(argv[2]);
		min_fold_change = atof(argv[3]);
		p.process(argv[1]);
	}
	else 
	{
		printf("%s: <sample-file> <max-mwu-pvalue> <min-fold-change\n", argv[0]);
		return 0;
	}

    return 0;
}
