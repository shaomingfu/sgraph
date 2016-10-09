#include <cstdio>
#include <cassert>
#include <sstream>

#include "gtf.h"
#include "config.h"

gtf::gtf(const string &file)
	: gm(file)
{
	build_boundary_positions();
	build_interval_map();
}

gtf::~gtf()
{
}

int gtf::build_boundary_positions()
{
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

int gtf::build_interval_map()
{
	jmap.clear();
	for(int i = 0; i < gm.genes.size(); i++)
	{
		gene &g = gm.genes[i];
		string chrm = g.get_seqname();
		for(int k = 0; k < g.transcripts.size(); k++)
		{
			transcript &t = g.transcripts[k];
			int abd = t.expression;

			for(int e = 0; e < t.exons.size(); e++)
			{
				int p1 = t.exons[e].first;
				int p2 = t.exons[e].second;

				if(jmap.find(chrm) == jmap.end())
				{
					join_interval_map m;
					m += make_pair(ROI(p1, p2), abd);
					jmap.insert(PSJIM(chrm, m));
				}
				else
				{
					jmap[chrm] += make_pair(ROI(p1, p2), abd);
				}
			}
		}
	}

	return 0;
}
