#include "block.h"

int block::index = 0;

int block::clear()
{
	chrm = "";
	pos = -1;
	s.clear();
	return 0;
}

int block::build_samples(const set<int32_t> &ss, const set<int32_t> &tt)
{
	block::index++;
	printf("%d %d ", block::index, pos);
	for(int i = 0; i < s.size(); i++)
	{
		int32_t p = i + pos;
		int label = 0;
		if(ss.find(p) != ss.end()) label = 1;
		if(tt.find(p) != tt.end()) label = -1;
		if(i == 0 && ltype == true) label = 1;
		if(i == s.size() - 1 && rtype == true) label = -1;
		printf("%d:%d:%d ", p, label, s[i]);
	}
	printf("\n");
	return 0;
}
