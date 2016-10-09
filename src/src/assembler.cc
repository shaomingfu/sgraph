#include <cstdio>
#include <cassert>
#include <sstream>

#include "config.h"
#include "assembler.h"
#include "bundle.h"
#include "genome.h"

assembler::assembler(const string &file)
	: gf(file)
{
}

assembler::~assembler()
{
}

int assembler::print()
{
	for(MSSI::iterator it = gf.mss.begin(); it != gf.mss.end(); it++)
	{
		set<int32_t> &s = it->second;
		for(set<int32_t>::iterator i = s.begin(); i != s.end(); i++)
		{
			printf("left %s %d\n", it->first.c_str(), *i);
		}
	}
	for(MSSI::iterator it = gf.mtt.begin(); it != gf.mtt.end(); it++)
	{
		set<int32_t> &s = it->second;
		for(set<int32_t>::iterator i = s.begin(); i != s.end(); i++)
		{
			printf("right %s %d\n", it->first.c_str(), *i);
		}
	}
	return 0;
}


int assembler::process(const string &file, const string &sample_file, const string &abundance_file)
{
    samFile *fn = sam_open(file.c_str(), "r");
    bam_hdr_t *h= sam_hdr_read(fn);
    bam1_t *b = bam_init1();

	sample_fout.open(sample_file.c_str());
	abundance_fout.open(abundance_file.c_str());

	bundle_base bb1;		// for + reads
	bundle_base bb2;		// for - reads
    while(sam_read1(fn, h, b) >= 0)
	{
		bam1_core_t &p = b->core;
		if((p.flag & 0x4) >= 1) continue;			// read is not mapped, TODO
		if((p.flag & 0x100) >= 1) continue;		// secondary alignment
		if(p.n_cigar < 1) continue;				// should never happen
		if(p.n_cigar > MAX_NUM_CIGAR) continue;	// ignore hits with more than 7 cigar types
		//if(p.qual <= 4) continue;				// ignore hits with quality-score < 5
		
		if(bb1.get_num_hits() > 0 && (bb1.get_rpos() + min_bundle_gap < p.pos || p.tid != bb1.get_tid()))
		{
			process_bundle(bb1, h);
		}

		if(bb2.get_num_hits() > 0 && (bb2.get_rpos() + min_bundle_gap < p.pos || p.tid != bb2.get_tid()))
		{
			process_bundle(bb2, h);
		}

		hit ht(b);
		if(ht.xs == '+') bb1.add_hit(ht);
		if(ht.xs == '-') bb2.add_hit(ht);
    }
	process_bundle(bb1, h);
	process_bundle(bb2, h);

    bam_destroy1(b);
    bam_hdr_destroy(h);
    sam_close(fn);

	sample_fout.close();
	abundance_fout.close();

	return 0;
}

int assembler::process_bundle(bundle_base &bb, bam_hdr_t *h)
{
	if(bb.get_num_hits() < min_num_hits_in_bundle) 
	{
		bb.clear();
		return 0;
	}

	char buf[1024];
	int tid = bb.get_tid();
	assert(tid >= 0);
	strcpy(buf, h->target_name[tid]);
	string chrm(buf);
	bb.set_chrm(chrm);

	bundle bd(bb);
	bd.build();

	set<int32_t> s1;
	set<int32_t> s2;
	join_interval_map jmap0;

	set<int32_t> &ss1 = s1;
	set<int32_t> &ss2 = s2;
	join_interval_map &jmap = jmap0;

	if(gf.mss.find(chrm) != gf.mss.end()) ss1 = gf.mss[chrm];
	if(gf.mtt.find(chrm) != gf.mtt.end()) ss2 = gf.mtt[chrm];
	if(gf.jmap.find(chrm) != gf.jmap.end()) jmap = gf.jmap[chrm];

	for(int i = 0; i < bd.blocks.size(); i++)
	{
		block &b = bd.blocks[i];
		b.build_labels(ss1, ss2);
		b.build_abundance(jmap);
		b.build_features();
		b.write_samples(sample_fout);
		b.write_abundance(abundance_fout);
	}

	bb.clear();
	return 0;
}
