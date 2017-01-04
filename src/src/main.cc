#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <iostream>
#include <ctime>

#include "assembler.h"
#include "config.h"
#include "block.h"

using namespace std;

int main(int argc, const char **argv)
{
	parse_arguments(argc, argv);

	block::index = index_prefix;

	assembler asmbl(argv[2], argv[3]);
	asmbl.process(argv[1], argv[4]);

    return 0;
}
