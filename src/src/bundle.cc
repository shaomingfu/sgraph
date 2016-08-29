#include <cassert>
#include <cstdio>
#include <map>
#include <iomanip>
#include <fstream>

#include "bundle.h"
#include "region.h"

bundle::bundle(const bundle_base &bb)
	: bundle_base(bb)
{
}

bundle::~bundle()
{}

int bundle::build()
{
	check_left_ascending();
	process_single_hits();
	infer_junctions();
	build_regions();
	build_blocks();
	return 0;
}

int bundle::check_left_ascending()
{
	for(int i = 1; i < hits.size(); i++)
	{
		int32_t p1 = hits[i - 1].pos;
		int32_t p2 = hits[i].pos;
		assert(p1 <= p2);
	}
	return 0;
}

int bundle::check_right_ascending()
{
	for(int i = 1; i < hits.size(); i++)
	{
		int32_t p1 = hits[i - 1].rpos;
		int32_t p2 = hits[i].rpos;
		assert(p1 <= p2);
	}
	return 0;
}

int bundle::infer_junctions()
{
	map<int64_t, junction> m;
	vector<int64_t> v;
	for(int i = 0; i < hits.size(); i++)
	{
		hits[i].get_splice_positions(v);
		if(v.size() == 0) continue;
		for(int k = 0; k < v.size(); k++)
		{
			int64_t p = v[k];
			if(m.find(p) == m.end()) 
			{
				junction sp(p, 1, hits[i].qual, hits[i].qual);
				m.insert(pair<int64_t, junction>(p, sp));
			}
			else
			{
				m[p].count++;
				if(hits[i].qual < m[p].min_qual) m[p].min_qual = hits[i].qual;
				if(hits[i].qual > m[p].max_qual) m[p].max_qual = hits[i].qual;
			}
		}
	}

	map<int64_t, junction>::iterator it;
	for(it = m.begin(); it != m.end(); it++)
	{
		if(it->second.count < min_splice_boundary_hits) continue;
		if(it->second.max_qual < min_max_splice_boundary_qual) continue;
		junctions.push_back(it->second);
	}
	return 0;
}

int bundle::process_single_hits()
{
	imap.clear();
	qmap.clear();
	for(int i = 0; i < hits.size(); i++)
	{
		hit &h = hits[i];
		int q = (int)(h.qual);
		vector<int64_t> v;
		h.get_matched_intervals(v);
		for(int k = 0; k < v.size(); k++)
		{
			int32_t s = high32(v[k]);
			int32_t t = low32(v[k]);
			imap += make_pair(ROI(s, t), 1);
			qmap += make_pair(ROI(s, t), q);
		}
	}
	return 0;
}

int bundle::build_regions()
{
	set<PPI> s;
	s.insert(PPI(lpos, START_BOUNDARY));
	s.insert(PPI(rpos, END_BOUNDARY));

	for(int i = 0; i < junctions.size(); i++)
	{
		s.insert(PPI(junctions[i].lpos, LEFT_SPLICE));
		s.insert(PPI(junctions[i].rpos, RIGHT_SPLICE));
	}

	vector<PPI> v(s.begin(), s.end());
	sort(v.begin(), v.end());

	for(int i = 0; i < v.size() - 1; i++)
	{
		int32_t lpos = v[i].first;
		int32_t rpos = v[i + 1].first;
		int ltype = v[i].second;
		int rtype = v[i + 1].second;
		
		region r(chrm, lpos, rpos, ltype, rtype, &imap, &qmap);
		regions.push_back(r);
	}
	return 0;
}

int bundle::build_blocks()
{
	for(int i = 0; i < regions.size(); i++)
	{
		region &r = regions[i];
		block b;
		r.build_block(b);
		if(b.s.size() == 0) continue;
		blocks.push_back(b);
	}
	return 0;
}

int bundle::print(int index) const
{
	printf("\nBundle %d: ", index);
	printf("tid = %d, #hits = %lu, range = %s:%d-%d, orient = %c\n",
			tid, hits.size(), chrm.c_str(), lpos, rpos, strand);

	// print junctions 
	for(int i = 0; i < junctions.size(); i++)
	{
		junctions[i].print(i);
	}

	return 0;
}
