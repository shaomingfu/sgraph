#ifndef __ASSEMBLER_H__
#define __ASSEMBLER_H__

#include <fstream>
#include <string>
#include <set>

#include "block.h"
#include "bundle_base.h"

using namespace std;

typedef pair< string, set<int32_t> > PSSI;
typedef map< string, set<int32_t> > MSSI;

class assembler
{
public:
	assembler();
	~assembler();

public:
	MSSI mss;
	MSSI mtt;

public:
	int process(const string &bam_file, const string &gtf_file);

protected:
	int build_boundary_positions(const string &file);
	int process_bam(const string &file);
	int process_bundle(bundle_base &bb, bam_hdr_t *h);
	int print();
};

#endif
