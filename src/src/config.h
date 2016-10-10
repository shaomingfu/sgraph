#ifndef __CONFIG_H__
#define __CONFIG_H__

#include "util.h"
#include <stdint.h>
#include <map>
#include <sstream>

using namespace std;

// constants
#define LEFT_SPLICE 1
#define RIGHT_SPLICE 2
#define LEFT_BOUNDARY 3
#define RIGHT_BOUNDARY 4
#define START_BOUNDARY 5
#define END_BOUNDARY 6

#define SLOPE5END 0
#define SLOPE3END 1

#define SLOPE_MARGIN 0
#define SLOPE_MIDDLE 1

// pre-defined parameters
#define MAX_NUM_CIGAR 7
#define MIN_LEN_FLANK 1

// user-defined parameters
extern int32_t min_bundle_gap;
extern int min_num_hits_in_bundle;
extern int32_t min_splice_boundary_hits;
extern uint32_t min_max_splice_boundary_qual;
extern double min_average_overlap;
extern int min_max_region_overlap;
extern int min_sample_length;
extern double min_transcript_expression;
extern double min_region_coverage;


// load and parse
int load_config(const char * conf_file);
int parse_arguments(int argc, const char ** argv);

#endif
