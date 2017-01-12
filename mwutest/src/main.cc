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
	if(argc == 5 && string(argv[1]) == "mwutest")
	{
		use_mwutest = true;
		predictor p;
		max_mwu_pvalue = atof(argv[3]);
		min_fold_change = atof(argv[4]);
		p.process(argv[2]);
	}
	else if(argc == 3 && string(argv[1]) == "trivial")
	{
		use_mwutest = false;
		predictor p;
		p.process(argv[2]);
	}
	else 
	{
		printf("%s: [trivial/mwutest] <sample-file> <max-mwu-pvalue> <min-fold-change>\n", argv[0]);
		return 0;
	}

    return 0;
}
