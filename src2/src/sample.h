#ifndef __SAMPLE_H__
#define __SAMPLE_H__

#include "position.h"
#include "block.h"
#include <vector>

using namespace std;

class sample
{
public:
	vector<position> positions;
	vector<block> blocks0;
	vector<block> blocks2;

	int correct0;
	int correct2;
	int label0;
	int label2;

public:
	int add_position(const string &s);
	int clear();
	int print();
	int process();

private:
	int build_blocks(int ff, vector<block> &blocks);
	int align_blocks(int ff, vector<block> &blocks, int &ncorrect, int &nlabel);
};

#endif
