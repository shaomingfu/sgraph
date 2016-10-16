#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <iostream>
#include <ctime>

#include "assembler.h"
#include "config.h"

using namespace std;

int main(int argc, const char **argv)
{
	if(argc == 5)
	{
		assembler asmbl(argv[2]);
		asmbl.process(argv[1], argv[3], argv[4]);
	}

	if(argc == 4)
	{
		assembler asmbl(argv[2]);
		asmbl.process(argv[1], argv[3], argv[4]);
	}

    return 0;
}
