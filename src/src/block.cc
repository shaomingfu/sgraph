#include "block.h"
#include "config.h"
#include <cassert>

int block::index = 0;

int block::clear()
{
	chrm = "";
	pos = -1;
	s.clear();
	q.clear();
	return 0;
}

int block::build_samples(const set<int32_t> &ss, const set<int32_t> &tt)
{
	assert(s.size() == q.size());
	if(s.size() < min_sample_length) return 0;

	block::index++;
	printf("# sample-id = %d, length = %lu, location = %s:%d-%lu\n", block::index, s.size(), chrm.c_str(), pos, pos + s.size());
	for(int i = 0; i < s.size(); i++)
	{
		int32_t p = i + pos;
		int label = 0;
		if(ss.find(p) != ss.end()) label = 1;
		if(tt.find(p) != tt.end()) label = -1;
		if(i == 0 && ltype == true) label = 1;
		if(i == s.size() - 1 && rtype == true) label = -1;
		printf("%d ", label);
	}
	printf("\n");

	for(int i = 0; i < s.size(); i++) printf("%d ", s[i]);
	printf("\n");

	for(int i = 0; i < q.size(); i++) printf("%.2lf ", q[i]);

	printf("\n");
	return 0;
}
