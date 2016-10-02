#include "sample.h"
#include "config.h"

#include <fstream>
#include <string>
#include <iostream>
#include <cstdlib>

using namespace std;

int main(int argc, const char ** argv)
{
	if(argc != 3) 
	{
		printf("usage: %s: <prediction-file> <probability-threshold>\n", argv[0]);
		return 0;
	}

	min_prob = atof(argv[2]);

	ifstream fin(argv[1]);
	if(fin.fail()) return 0;

	sample sp;

	int correct0 = 0;
	int correct2 = 0;
	int label0 = 0;
	int label2 = 0;
	int pred0 = 0;
	int pred2 = 0;

	int index = -1;
	string s;
	while(getline(fin, s))
	{
		if(s.size() == 0) continue;
		if(s[0] == '#')
		{
			index++;
			if(index == 0) continue;
			printf("sample %d: ", index);
			sp.process();

			correct0 += sp.correct0;
			correct2 += sp.correct2;
			label0 += sp.label0;
			label2 += sp.label2;
			pred0 += sp.blocks0.size();
			pred2 += sp.blocks2.size();

			sp.clear();
		}
		else
		{
			sp.add_position(s);
		}
	}

	printf("summary label0 = %d / %d / %d (corrrect / prediction / label), sensitivity = %.3lf, precision = %.3lf\n", correct0, pred0, label0, correct0 * 1.0 / label0, correct0 * 1.0 / pred0);
	printf("summary label2 = %d / %d / %d (corrrect / prediction / label), sensitivity = %.3lf, precision = %.3lf\n", correct2, pred2, label2, correct2 * 1.0 / label2, correct2 * 1.0 / pred2);

	fin.close();
	return 0;
}
