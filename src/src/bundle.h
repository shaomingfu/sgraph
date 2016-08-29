#ifndef __BUNDLE_H__
#define __BUNDLE_H__

#include "interval_map.h"
#include "bundle_base.h"
#include "junction.h"
#include "region.h"
#include "block.h"

using namespace std;

class bundle : public bundle_base
{
public:
	bundle(const bundle_base &bb);
	virtual ~bundle();

public:
	vector<junction> junctions;		// splice junctions
	vector<region> regions;			// regions
	split_interval_map imap;		// interval map
	split_interval_map qmap;		// quality map
	vector<block> blocks;			// blocks

public:
	int build();
	int print(int index) const;

protected:
	int check_left_ascending();
	int check_right_ascending();
	int infer_junctions();
	int process_single_hits();
	int build_regions();
	int build_blocks();
};

#endif
