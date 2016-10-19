#include "pinpoint.h"
#include "config.h"

#include <fstream>
#include <string>
#include <iostream>
#include <cstdlib>
#include <sstream>

using namespace std;

pinpoint::pinpoint(const string &prd_file, const string &abd_file)
{
	fprd.open(prd_file.c_str());
	fabd.open(abd_file.c_str());

	correct0 = 0;
	correct1 = 0;
	correct2 = 0;
	label0 = 0;
	label1 = 0;
	label2 = 0;
	predict0 = 0;
	predict1 = 0;
	predict2 = 0;

	nsample = 0;
	abdratio = 0;

	index = 0;
}

pinpoint::~pinpoint()
{
	fprd.close();
	fabd.close();
}

int pinpoint::load_prediction()
{
	string line;
	while(getline(fprd, line))
	{
		if(line.size() == 0) continue;
		if(line[0] == '#' && index >= 1) break;
		if(line[0] == '#' && index == 0) index++;
		if(line[0] != '#') sp.add_position(line);
	}
	return 0;
}

int pinpoint::load_abundance()
{
	stringstream sstr;
	string line;
	while(getline(fabd, line))
	{
		if(line.size() == 0) continue;
		if(line[0] != '#') continue;

		// true label
		int k = 0;
		getline(fabd, line);
		sstr.clear();
		sstr<<line.c_str();
		while(sstr>>sp.positions[k++].tlab){}

		// for read abundance
		k = 0;
		getline(fabd, line);
		sstr.clear();
		sstr<<line.c_str();
		while(sstr>>sp.positions[k++].rabd){}

		// for true abundance
		k = 0;
		getline(fabd, line);
		sstr.clear();
		sstr<<line.c_str();
		while(sstr>>sp.positions[k++].tabd){}

		// for true abundance label
		k = 0;
		getline(fabd, line);
		sstr.clear();
		sstr<<line.c_str();
		while(sstr>>sp.positions[k++].alab){}

		break;
	}

	return 0;
}

bool pinpoint::process()
{
	if(sp.positions.size() == 0) return false;

	sp.process();
	if(sp.accept == false) 
	{
		sp.clear();
		return true;
	}

	sp.print(index++);

	correct0 += sp.correct0;
	correct1 += sp.correct1;
	correct2 += sp.correct2;
	label0 += sp.label0;
	label1 += sp.label1;
	label2 += sp.label2;
	predict0 += sp.predict0;
	predict1 += sp.predict1;
	predict2 += sp.predict2;

	nsample++;
	abdratio += sp.abdratio;

	sp.clear();
	return true;
}

int pinpoint::solve()
{
	while(true)
	{
		load_prediction();
		load_abundance();
		bool b = process();
		if(b == false) break;
	}

	printf("summary label0 = %d / %d / %d (corrrect / prediction / label), sensitivity = %.3lf, precision = %.3lf\n", correct0, predict0, label0, correct0 * 1.0 / label0, correct0 * 1.0 / predict0);
	printf("summary label2 = %d / %d / %d (corrrect / prediction / label), sensitivity = %.3lf, precision = %.3lf\n", correct2, predict2, label2, correct2 * 1.0 / label2, correct2 * 1.0 / predict2);
	printf("summary label1 = %d / %d / %d (corrrect / prediction / label), sensitivity = %.3lf, precision = %.3lf\n", correct1, predict1, label1, correct1 * 1.0 / label1, correct1 * 1.0 / predict1);

	abdratio /= nsample;
	printf("summary abundance, %d samples with 0 or 2 labels, average deviation = %.3lf\n", nsample, abdratio);

	return 0;
}
