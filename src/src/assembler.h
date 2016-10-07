#ifndef __ASSEMBLER_H__
#define __ASSEMBLER_H__

#include <fstream>
#include <string>
#include <set>

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

public:
	int process(const string &bam_file);

protected:
	int build_boundary_positions(const string &file);
	int process_bam(const string &file);
	int process_bundle(bundle_base &bb, bam_hdr_t *h);
	int print();
};

#endif
