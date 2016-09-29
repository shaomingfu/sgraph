#include <cstdio>
#include <cassert>
#include <sstream>

#include "config.h"
#include "assembler.h"
#include "bundle.h"
#include "genome.h"

assembler::assembler()
{
}

assembler::~assembler()
{
}

int assembler::process(const string &bam_file, const string &gtf_file)
{
	build_boundary_positions(gtf_file);
	process_bam(bam_file);
	//print();
	return 0;
}

int assembler::print()
{
	for(MSSI::iterator it = mss.begin(); it != mss.end(); it++)
	{
		set<int32_t> &s = it->second;
		for(set<int32_t>::iterator i = s.begin(); i != s.end(); i++)
		{
			printf("left %s %d\n", it->first.c_str(), *i);
		}
	}
	for(MSSI::iterator it = mtt.begin(); it != mtt.end(); it++)
	{
		set<int32_t> &s = it->second;
		for(set<int32_t>::iterator i = s.begin(); i != s.end(); i++)
		{
			printf("right %s %d\n", it->first.c_str(), *i);
		}
	}
	return 0;
}

int assembler::build_boundary_positions(const string &file)
{
	genome gm(file);
	mss.clear();
	mtt.clear();

	for(int i = 0; i < gm.genes.size(); i++)
	{
		gene &g = gm.genes[i];
		string chrm = g.get_seqname();
		for(int k = 0; k < g.transcripts.size(); k++)
		{
			transcript &t = g.transcripts[k];
			PI32 p = t.get_bounds();
			if(p.first < 0 || p.second < 0) continue;
			if(t.expression < min_transcript_expression) continue;

			if(mss.find(chrm) == mss.end())
			{
				set<int32_t> s;
				s.insert(p.first);
				mss.insert(PSSI(chrm, s));
			}
			else
			{
				mss[chrm].insert(p.first);
			}

			if(mtt.find(chrm) == mtt.end())
			{
				set<int32_t> s;
				s.insert(p.second);
				mtt.insert(PSSI(chrm, s));
			}
			else
			{
				mtt[chrm].insert(p.second);
			}
		}
	}

	return 0;
}

int assembler::process_bam(const string &file)
{
    samFile *fn = sam_open(file.c_str(), "r");
    bam_hdr_t *h= sam_hdr_read(fn);
    bam1_t *b = bam_init1();

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

	set<int32_t> &ss1 = s1;
	set<int32_t> &ss2 = s2;

	if(mss.find(chrm) != mss.end()) ss1 = mss[chrm];
	if(mtt.find(chrm) != mtt.end()) ss2 = mtt[chrm];

	for(int i = 0; i < bd.blocks.size(); i++)
	{
		block &b = bd.blocks[i];
		b.build_labels(ss1, ss2);
		b.build_features();
		b.write_samples();
	}

	bb.clear();
	return 0;
}
