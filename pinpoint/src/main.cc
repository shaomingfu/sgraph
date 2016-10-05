#include "sample.h"
#include "config.h"

#include <fstream>
#include <string>
#include <iostream>
#include <cstdlib>

using namespace std;

int main(int argc, const char ** argv)
{
	if(argc != 7) 
	{
		printf("usage: %s: <prediction-file> <probability-threshold (for 0 and 2)> <half-window-size-for-average (for 0 and 2)> <half-window-size-for-correct (for 0 and 2)> <probability-threshold (for 1)> <half-window-size-for-average (for 1)> \n", argv[0]);
		return 0;
	}

	min_prob = atof(argv[2]);
	block_size = 2 * atoi(argv[3]);
	max_correct_distance = 2 * atoi(argv[4]);

	min_prob1 = atof(argv[5]);
	block_size1 = atoi(argv[6]);

	ifstream fin(argv[1]);
	if(fin.fail()) return 0;

	sample sp;

	int correct0 = 0;
	int correct1 = 0;
	int correct2 = 0;
	int label0 = 0;
	int label1 = 0;
	int label2 = 0;
	int predict0 = 0;
	int predict1 = 0;
	int predict2 = 0;

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
			correct1 += sp.correct1;
			correct2 += sp.correct2;
			label0 += sp.label0;
			label1 += sp.label1;
			label2 += sp.label2;
			predict0 += sp.predict0;
			predict1 += sp.predict1;
			predict2 += sp.predict2;

			sp.clear();
		}
		else
		{
			sp.add_position(s);
		}
	}

	printf("summary label0 = %d / %d / %d (corrrect / prediction / label), sensitivity = %.3lf, precision = %.3lf\n", correct0, predict0, label0, correct0 * 1.0 / label0, correct0 * 1.0 / predict0);
	printf("summary label2 = %d / %d / %d (corrrect / prediction / label), sensitivity = %.3lf, precision = %.3lf\n", correct2, predict2, label2, correct2 * 1.0 / label2, correct2 * 1.0 / predict2);
	printf("summary label1 = %d / %d / %d (corrrect / prediction / label), sensitivity = %.3lf, precision = %.3lf\n", correct1, predict1, label1, correct1 * 1.0 / label1, correct1 * 1.0 / predict1);

	fin.close();
	return 0;
}
