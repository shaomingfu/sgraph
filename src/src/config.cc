#include "config.h"
#include <cstdlib>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <cstring>

using namespace std;

//// parameters

// for bam file
int32_t min_bundle_gap = 50;
int min_num_hits_in_bundle = 20;
int32_t min_splice_boundary_hits = 1;
uint32_t min_max_splice_boundary_qual = 3;
double min_average_overlap = 2;
int min_max_region_overlap = 5;
int min_sample_length = 100;
double min_transcript_expression = 50.0;
double min_region_coverage = 10.0;

int parse_arguments(int argc, const char ** argv)
{
	for(int i = 1; i < argc; i++)
	{
		if(string(argv[i]) == "-c")
		{
			load_config(argv[i + 1]);
			i++;
		}
	}
	return 0;
}

int load_config(const char * conf_file)
{
	ifstream fin(conf_file);
	if(fin.fail())
	{
		cout<<"open config file error "<<conf_file<<endl;
		return -1;
	}

	char buf[1024];
	char key[1024];
	char value[1024];
	
	while(fin.getline(buf, 1024, '\n'))
	{
		stringstream sstr(buf);
		sstr>>key>>value;

		if(strcmp(key, "min_num_hits_in_bundle")==0)
		{
			min_num_hits_in_bundle = (int)atoi(value);
		}
	}

	return 0;
}
