#include "pinpoint.h"

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

		// for true abundance
		k = 0;
		getline(fabd, line);
		sstr.clear();
		sstr<<line.c_str();
		while(sstr>>sp.positions[k++].tabd){}

		// for read abundance
		k = 0;
		getline(fabd, line);
		sstr.clear();
		sstr<<line.c_str();
		while(sstr>>sp.positions[k++].rabd){}

		getline(fabd, line);
		getline(fabd, line);
		getline(fabd, line);
		getline(fabd, line);
		getline(fabd, line);
		getline(fabd, line);
		getline(fabd, line);
		getline(fabd, line);
		getline(fabd, line);
		getline(fabd, line);
		getline(fabd, line);
		getline(fabd, line);
		getline(fabd, line);

		break;
	}

	return 0;
}

bool pinpoint::process()
{
	if(sp.positions.size() == 0) return false;

	//printf("process sample %d with %lu positions\n", index, sp.positions.size());

	sp.process();
	sp.print(index++);

	if(sp.boundary() == true)
	{
		nsample++;
		abdratio += sp.abdratio;
	}

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

	abdratio /= nsample;
	printf("summary abundance, %d samples with 0 or 2 labels, average deviation = %.3lf\n", nsample, abdratio);

	return 0;
}
