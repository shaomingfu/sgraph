#ifndef __ASSEMBLER_H__
#define __ASSEMBLER_H__

#include <fstream>
#include <string>
#include <set>
#include <fstream>

#include "gtf.h"
#include "block.h"
#include "bundle_base.h"

using namespace std;

class assembler
{
public:
	assembler(const string &gtf_file);
	~assembler();

public:
	gtf gf;
	ofstream sample_fout;
	ofstream abundance_fout;

public:
	int build_boundary_positions(const string &file);
	int process_bundle(bundle_base &bb, bam_hdr_t *h);
	int process(const string &file, const string &sample_file, const string &abundance_file);
	int print();
};

#endif
