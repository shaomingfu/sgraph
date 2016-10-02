#include "sample.h"
#include "config.h"
#include <cstdio>
#include <cassert>
#include <algorithm>
#include <set>

int sample::add_position(const string &s)
{
	position p(s);
	positions.push_back(p);
	return 0;
}

int sample::clear()
{
	positions.clear();
	blocks0.clear();
	blocks2.clear();
	correct0 = correct2 = 0;
	label0 = label2 = 0;
	return 0;
}

int sample::process()
{
	build_blocks(0, blocks0);
	build_blocks(2, blocks2);
	align_blocks(0, blocks0, correct0, label0);
	align_blocks(2, blocks2, correct2, label2);
	print();
	return 0;
}

int sample::build_blocks(int ff, vector<block> &blocks)
{
	blocks.clear();
	if(positions.size() < block_size) return 0;

	double pr = 0;
	int cnt = 0;
	for(int i = 0; i < block_size; i++)
	{
		position &p = positions[i];
		pr += p.pp;
		if(p.pred == ff) cnt++;
	}

	for(int i = 0; i < positions.size() - block_size; i++)
	{
		position &p1 = positions[i];
		position &p2 = positions[i + block_size];
		pr += p2.pp;
		pr -= p1.pp;
		if(p2.pred == ff) cnt++;
		if(p1.pred == ff) cnt--;
		assert(cnt <= block_size);

		double ave = pr * 1.0 / block_size;
		if(cnt < block_size) continue;
		if(ave < min_prob) continue;

		blocks.push_back(block(i, ave));
	}

	sort(blocks.begin(), blocks.end());

	vector<block> vv;
	for(int i = 0; i < blocks.size(); i++)
	{
		block &b = blocks[i];
		bool f = false;
		for(int k = 0; k < vv.size(); k++)
		{
			if(b.distance(vv[k]) < min_block_distance) f = true;
			if(f == true) break;
		}
		if(f == true) continue;
		vv.push_back(b);
	}

	blocks = vv;
	return 0;
}

int sample::align_blocks(int ff, vector<block> &blocks, int &ncorrect, int &nlabel)
{
	vector<PI> vv;
	for(int i = 0; i < positions.size(); i++)
	{
		position &p = positions[i];
		if(p.label != ff) continue;
		vv.push_back(PI(i, -1));
	}
	nlabel = vv.size();
	ncorrect = 0;

	for(int i = 0; i < blocks.size(); i++)
	{
		block &b = blocks[i];
		vv.push_back(PI(b.pos, i));
	}

	sort(vv.begin(), vv.end());

	set<int> s;
	for(int i = 0; i < vv.size(); i++)
	{
		int p = vv[i].first;
		int k = vv[i].second;
		if(k == -1) continue;

		int p1 = max_correct_distance * 2;
		int p2 = max_correct_distance * 2;

		if(i >= 1 && vv[i - 1].second == -1 && s.find(i - 1) == s.end()) p1 = p - vv[i - 1].first;
		if(i < vv.size() - 1 && vv[i + 1].second == -1 && s.find(i + 1) == s.end()) p2 = vv[i + 1].first - p;

		if(p1 < max_correct_distance && p1 <= p2)
		{
			blocks[k].match = p1;
			s.insert(i - 1);
			ncorrect++;
		}
		if(p2 < max_correct_distance && p2 < p1)
		{
			blocks[k].match = p2;
			s.insert(i + 1);
			ncorrect++;
		}
	}
	return 0;
}

int sample::print()
{
	printf("positions = %lu, label0 = %d / %lu / %d, label2 = %d / %lu / %d\n", positions.size(), 
			correct0, blocks0.size(), label0, 
			correct2, blocks2.size(), label2); 

	return 0;

	// print blocks
	for(int i = 0; i < blocks0.size(); i++)
	{
		printf("block0 %d (size = %lu): ", i, positions.size());
		blocks0[i].print();
		int p = blocks0[i].pos;
		positions[p].print();
	}
	for(int i = 0; i < blocks2.size(); i++)
	{
		printf("block2 %d (size = %lu): ", i, positions.size());
		blocks2[i].print();
		int p = blocks2[i].pos;
		positions[p].print();
	}
	return 0;
}
