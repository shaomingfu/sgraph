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
	if(argc != 3)
	{
		cout<<"usage: "<<argv[0]<<" bam-file gtf-file"<<endl;	
		return 0;
	}

	assembler asmbl;
	asmbl.process(argv[1], argv[2]);

    return 0;
}
