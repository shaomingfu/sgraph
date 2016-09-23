#include "fscore.h"
#include <cstdio>

int fscore::init(int k)
{
	sa.assign(k, -1);
	sb.assign(k, -1);
	va.assign(k, -1);
	vb.assign(k, -1);
	return 0;
}

int fscore::write()
{
	for(int i = 0; i < sa.size(); i++) printf("%d ", sa[i]); printf("\n");
	for(int i = 0; i < sb.size(); i++) printf("%d ", sb[i]); printf("\n");
	for(int i = 0; i < va.size(); i++) printf("%.2lf ", va[i]); printf("\n");
	for(int i = 0; i < vb.size(); i++) printf("%.2lf ", vb[i]); printf("\n");
	return 0;
}
